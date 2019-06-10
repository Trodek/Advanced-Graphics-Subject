#include "model.h"
#include "resourcemanager.h"
#include <iostream>
#include <QFile>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/importerdesc.h>
#include <assimp/cfileio.h>
#include <assimp/cimport.h>
#include "mesh.h"

Model::Model() : Resource(Resource::Type::Model)
{

}

Model::~Model()
{
    destroy();
}

void Model::update()
{
    for(Mesh* m : meshes)
    {
        m->update();
    }
}

void Model::destroy()
{
    for(int i = meshes.count()-1; i>=0;--i)
    {
        meshes[i]->destroy();
        meshes.removeAt(i);
    }
}

void Model::addMesh(VertexFormat vertFormat, void *data, int bytes)
{
    Mesh* m = new Mesh(vertFormat,data,bytes);
    meshes.push_back(m);
}

void Model::addMesh(VertexFormat vertFormat, void *data, int bytes, unsigned int *indexes, int index_count)
{
    Mesh* m = new Mesh(vertFormat,data,bytes,indexes,index_count);
    meshes.push_back(m);
}


void Model::loadModel(const std::string &path)
{
    // read file via ASSIMP
    Assimp::Importer importer;

    const aiScene* scene = aiImportFile(
                path.c_str(),
                aiProcess_Triangulate |
                aiProcess_FlipUVs |
                aiProcess_CalcTangentSpace |
                aiProcess_GenSmoothNormals |
                aiProcess_PreTransformVertices |
                aiProcess_OptimizeMeshes);

    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::string s = "ERROR::ASSIMP:: "; s += importer.GetErrorString();
        std::cout << s << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    this->path = ResourceManager::Instance()->GetPathFrom(path).c_str();
    this->name = ResourceManager::Instance()->GetNameFrom(path).c_str();

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
    std::cout <<"Succesfully loaded model with path: " << path << std::endl;
}

void Model::DrawMeshes()
{
    for(Mesh* m : meshes)
    {
        m->draw();
    }
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    QVector<float> vertices;
    QVector<uint> indices;

    bool hasTexCoords = false;
    bool hasTangentSpace = false;

    //process vertices
    for(uint i = 0; i< mesh->mNumVertices;++i)
    {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);

        if(mesh->mTextureCoords[0])
        {
            hasTexCoords = true;
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }

        if(mesh->mTangents != nullptr && mesh->mBitangents != nullptr)
        {
            hasTangentSpace = true;
            vertices.push_back(mesh->mTangents[i].x);
            vertices.push_back(mesh->mTangents[i].y);
            vertices.push_back(mesh->mTangents[i].z);
            vertices.push_back(mesh->mBitangents[i].x);
            vertices.push_back(mesh->mBitangents[i].y);
            vertices.push_back(mesh->mBitangents[i].z);
        }
    }

    //process indices
    for(uint i = 0; i < mesh->mNumFaces;i++)
    {
        aiFace face = mesh->mFaces[i];
        for(uint j = 0; j < face.mNumIndices;++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    VertexFormat vertexFormat;
    vertexFormat.SetVertexAttribute(0,0,3);
    vertexFormat.SetVertexAttribute(1,3*sizeof(float),3);

    if(hasTexCoords)
        vertexFormat.SetVertexAttribute(2,6*sizeof(float),2);

    if(hasTangentSpace)
    {
        vertexFormat.SetVertexAttribute(3,8*sizeof(float),3);
        vertexFormat.SetVertexAttribute(4,11*sizeof(float),3);
    }

    return new Mesh(vertexFormat,&vertices[0], vertices.size()*sizeof(float),&indices[0],indices.size());
}
