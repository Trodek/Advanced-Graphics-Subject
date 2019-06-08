#include "resourcemanager.h"
#include "model.h"
#include <QDirIterator>
#include <iostream>
#include <QDir>

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

Model *ResourceManager::GetModel(QString path) const
{
    for(Resource* res : resources)
    {
        if(res->type == Resource::Type::Model &&res->path == path)
            return (Model*)res;
    }
    return  nullptr;
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

Resource::Resource(Resource::Type type) : type(type)
{
}

Resource::~Resource()
{

}
