#include "scene.h"
#include "gameobject.h"
#include <iostream>
#include <QJsonArray>
#include "appmanager.h"

Scene* Scene::instance = nullptr;

Scene::Scene()
{

}

Scene::~Scene()
{
    for(GameObject* go : objects)
    {
        delete go;
    }
    objects.clear();
}

Scene *Scene::Instance()
{
    if(instance == nullptr)
    {
        instance = new Scene();
    }

    return instance;
}

GameObject *Scene::GetGameObject(int id) const
{
    if(id < objects.size())
        return objects[id];
    return  nullptr;
}

int Scene::NumGameObjects() const
{
    return objects.size();
}

void Scene::AddGameObject(GameObject *go)
{
    if(go != nullptr)
        objects.push_back(go);
}

void Scene::RemoveGameObject(int id)
{
    if(id < objects.size())
    {
        int i = 0;
        for(std::vector<GameObject*>::iterator go = objects.begin(); go != objects.end();go++)
        {
            if(i == id)
            {
                delete *go;
                objects.erase(go);
                break;
            }
            i++;
        }
    }
}

void Scene::RemoveGameObject(GameObject *go)
{
    for(std::vector<GameObject*>::iterator o = objects.begin(); o != objects.end();o++)
    {
        if(go == *o)
        {
            delete *o;
            objects.erase(o);
            break;
        }
    }
}

void Scene::NewScene()
{
    for(std::vector<GameObject*>::iterator o = objects.begin(); o != objects.end();o++)
    {
        delete *o;
    }
    objects.clear();
    selected = nullptr;
}

GameObject *Scene::GetSelectedGameObject() const
{
    return selected;
}

void Scene::SetSelectedGameObject(GameObject* id)
{
    selected = id;
    std::cout<< id->GetName()<< std::endl;
}

std::vector<GameObject *> Scene::GetObjectsToDraw() const
{
    std::vector<GameObject*> objectsDraw;
    for(std::vector<GameObject*>::const_iterator o = objects.begin(); o != objects.end();o++)
    {
        if((*o)->GetComponentByType(Component::Type::ModelRenderer) != nullptr)
            objectsDraw.push_back(*o);
    }
    return objectsDraw;
}

void Scene::SaveScene(QJsonObject &file) const
{
    QJsonArray gameObjects;
    for(std::vector<GameObject*>::const_iterator o = objects.begin(); o != objects.end();o++)
    {
        QJsonObject goObject;
        (*o)->Save(goObject);
        gameObjects.append(goObject);

    }
    file["GameObjects"] = gameObjects;
}

void Scene::LoadScene(const QJsonObject &file)
{
    if(file.contains("GameObjects") && file["GameObjects"].isArray())
    {
        QJsonArray gameObjects = file["GameObjects"].toArray();
        for(int i = 0; i< gameObjects.size();++i)
        {
            QJsonObject goData = gameObjects[i].toObject();

            //cheating :)
            AppManager::Instance()->GetHierarchy()->AddGameObject();
            GameObject* go = GetSelectedGameObject();
            go->Load(goData);
            emit AppManager::Instance()->GetInspector()->UpdateName();
        }
        //cheating :)
        emit AppManager::Instance()->GetHierarchy()->UpdateInspector();
    }
}
