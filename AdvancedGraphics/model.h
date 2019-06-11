#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "resourcemanager.h"
#include "texture.h"

#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ShaderProgram;

class Model : public Resource
{
public:
    Model();
    ~Model();

    void update();
    void destroy();

    void addMesh(VertexFormat vertFormat, void* data, int bytes);
    void addMesh(VertexFormat vertFormat, void* data, int bytes, unsigned int* indexes, int num_index);
    void loadModel(const std::string& path);

    void DrawMeshes(ShaderProgram* shader);

    QVector<Mesh*> meshes;

private:
    //Assimp shit
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh *mesh, const aiScene* scene);
    class Texture* loadMaterial(aiMaterial* mat, aiTextureType type);
};

#endif // MODEL_H
