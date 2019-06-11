#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QString>
#include <QVector>

class Model;
class ShaderProgram;
class Texture;
class Material;

class Resource
{
public:
    enum Type
    {
        Null,
        Model,
        Texture,
        Shader,
        Material,
    };
public:
    Resource(Type type);
    virtual ~Resource();

    virtual void update() = 0;
    virtual void destroy() = 0;

public:
    QString name = "";
    QString path = "";
    Type type = Type::Null;

};

class ResourceManager
{
public:
    static ResourceManager *Instance();

    ResourceManager();
    ~ResourceManager();

    Model* CreateModel();
    Model* GetModel(QString name) const;
    QVector<Model*> GetAllModels() const;

    ShaderProgram* CreateShaderProgram();
    ShaderProgram* GetShaderProgram(QString name) const;
    QVector<ShaderProgram*> GetAllShaderPrograms()const;

    Texture* CreateTexture();
    Texture* GetTexture(QString name)const;
    QVector<Texture*> GetAllTextures()const;

    Material* CreateMaterial();
    Material *GetMaterial(QString name) const;
    QVector<Material*> GetAllMaterials()const;

    void CreateSphere();
    void CreateQuad();

    void ClearResources();

    std::string GetPathFrom(std::string path);
    std::string GetNameFrom(std::string path);
    std::string GetExtensionFrom(std::string path);

private:
    static ResourceManager* instance;
    QVector<Resource*> resources;

};

#endif // RESOURCEMANAGER_H
