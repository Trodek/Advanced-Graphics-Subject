#include "resourcemanager.h"
#include "model.h"
#include "shaderprogram.h"
#include <QDirIterator>
#include <iostream>
#include <QDir>
#include "texture.h"

#define H 32
#define V 16

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager *ResourceManager::Instance()
{
    if(instance == nullptr)
    {
        instance = new ResourceManager();
    }

    return instance;
}

ResourceManager::ResourceManager()
{   

}

ResourceManager::~ResourceManager()
{
}

Model *ResourceManager::CreateModel()
{
    Model* ret = new Model();

    resources.push_back(ret);

    return  ret;
}

Model *ResourceManager::GetModel(QString name) const
{
    for(Resource* res : resources)
    {
        if(res->type == Resource::Type::Model &&res->name == name)
            return (Model*)res;
    }
    return  nullptr;
}

QVector<Model *> ResourceManager::GetAllModels() const
{
    QVector<Model*> models;
    for(Resource* res : resources)
    {
        if(res->type == Resource::Type::Model)
            models.push_back((Model*)res);
    }
    return models;
}

ShaderProgram *ResourceManager::CreateShaderProgram()
{
    ShaderProgram* ret = new ShaderProgram();

    resources.push_back(ret);

    return ret;
}

ShaderProgram *ResourceManager::GetShaderProgram(QString name) const
{
    for(Resource* res : resources)
    {
        if(res->type == Resource::Type::Shader &&res->name == name)
            return (ShaderProgram*)res;
    }
    return  nullptr;
}

QVector<ShaderProgram *> ResourceManager::GetAllShaderPrograms() const
{
    QVector<ShaderProgram*> shaders;
    for(Resource* res : resources)
    {
        if(res->type == Resource::Type::Shader)
            shaders.push_back((ShaderProgram*)res);
    }
    return shaders;
}

Texture *ResourceManager::CreateTexture()
{
    Texture* t = new Texture();
    resources.push_back(t);
    return t;
}

Texture *ResourceManager::GetTexture(QString name) const
{
    for(Resource* res : resources)
    {
        if(res->type == Resource::Type::Texture &&res->name == name)
            return (Texture*)res;
    }
    return  nullptr;
}

QVector<Texture *> ResourceManager::GetAllTextures() const
{
    QVector<Texture*> shaders;
    for(Resource* res : resources)
    {
        if(res->type == Resource::Type::Texture)
            shaders.push_back((Texture*)res);
    }
    return shaders;
}

void ResourceManager::CreateSphere()
{
    //create sphere test
    float pi = 3.1416f;
    struct Vertex {QVector3D pos; QVector3D norm;};
    Vertex sphere[H][V+1];
    for(int h = 0; h<H;++h)
    {
        for(int v = 0; v< V+1;++v)
        {
            float nh = float(H)/32;
            float nv = float(v)/V-0.5f;
            float angleh = 2*pi*nh;
            float anglev = -pi*nv;
            sphere[h][v].pos.setX(sinf(angleh)*cosf(anglev));
            sphere[h][v].pos.setY(-sinf(anglev));
            sphere[h][v].pos.setZ(cosf(angleh)*cosf(anglev));
            sphere[h][v].norm = sphere[h][v].pos;
        }
    }

    unsigned int sphereIndices[H][V][6];
    for(unsigned int h = 0; h < H; h++)
    {
        for(unsigned int v = 0; v< V;++v)
        {
            sphereIndices[h][v][0] = (h+0)     * (V+1) + v;
            sphereIndices[h][v][1] = ((h+1)%H) * (V+1) + v;
            sphereIndices[h][v][2] = ((h+1)%H) * (V+1) + v+1;
            sphereIndices[h][v][3] = (h+0)     * (V+1) + v;
            sphereIndices[h][v][4] = ((h+1)%H) * (V+1) + v+1;
            sphereIndices[h][v][5] = (h+0)     * (V+1) + v+1;
        }
    }

    VertexFormat vertFormat;
    vertFormat.SetVertexAttribute(0,0,3);
    vertFormat.SetVertexAttribute(1,sizeof(QVector3D),3);

    Model* model = CreateModel();
    model->name = "Sphere";
    model->addMesh(vertFormat,sphere,sizeof(sphere), &sphereIndices[0][0][0],H*V*6);
}

void ResourceManager::CreateQuad()
{
    QVector3D vertices[] = {
        QVector3D(-0.5f, 0.5f,0.0f), QVector3D(1.0f,0.0f,0.0f),
        QVector3D(-0.5f,-0.5f,0.0f), QVector3D(0.0f,1.0f,0.0f),
        QVector3D(0.5f,-0.5f,0.0f), QVector3D(0.0f,0.0f,1.0f),
        QVector3D(0.5f,0.5f,0.0f), QVector3D(0.0f,0.0f,0.0f)
    };

    uint indices[] {
        0, 1, 2,
        0, 2, 3
    };

    const GLint compCount = 3;
    const int offset0 = 0;
    const int offset1 = sizeof(QVector3D);

    VertexFormat format;
    format.SetVertexAttribute(0,offset0,compCount);
    format.SetVertexAttribute(1,offset1,compCount);

    Model* m = CreateModel();
    m->addMesh(format,vertices,8*sizeof(QVector3D),indices,6);
    m->name = "Quad";

}

void ResourceManager::ClearResources()
{
    for(int i = resources.count() - 1; i>= 0; --i)
    {
        delete resources[i];
        resources.remove(i);
    }
    resources.clear();
}

std::string ResourceManager::GetPathFrom(std::string path)
{
    return path.substr(0, path.find_last_of('/'));
}

std::string ResourceManager::GetNameFrom(std::string path)
{
    return path.substr(path.find_last_of('/')+1, path.size() - (path.find_last_of('/')+1) - GetExtensionFrom(path).size()-1);
}

std::string ResourceManager::GetExtensionFrom(std::string path)
{
    return path.substr(path.find_last_of('.')+1,path.size() - path.find_last_of('.')+1);
}

Resource::Resource(Resource::Type type) : type(type)
{
}

Resource::~Resource()
{

}
