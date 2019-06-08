#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "resourcemanager.h"

class aiNode;
class aiMesh;
class aiScene;

class Model : public Resource
{
public:
    Model();
    ~Model();

    void update(){}
    void destroy(){}

    void addMesh(VertexFormat vertFormat, void* data, int bytes);
    void addMesh(VertexFormat vertFormat, void* data, int bytes, unsigned int* indexes, int bytes_indexes);
    void loadModel(const std::string& path);

    QVector<Mesh*> meshes;

private:
    //Assimp shit
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh *mesh, const aiScene* scene);
};

#endif // MODEL_H
