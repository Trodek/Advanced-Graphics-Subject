#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QString>
#include <QVector>

class Model;

class Resource
{
public:
    enum Type
    {
        Null,
        Model,
        Texture,
        Material,
    };
public:
    Resource(Type type);
    virtual ~Resource();

    virtual void update() = 0;
    virtual void destroy() = 0;

public:
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

    Model* GetModel(QString path) const;

    void ClearResources();

private:
    static ResourceManager* instance;
    QVector<Resource*> resources;

};

#endif // RESOURCEMANAGER_H
