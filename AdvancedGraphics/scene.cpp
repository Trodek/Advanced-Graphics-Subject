#include "scene.h"
#include "gameobject.h"

Scene* Scene::instance = nullptr;

Scene::Scene()
{
    //Test go
    GameObject* go = new GameObject();
    go->SetName("SimonLaXupa");
    AddGameObject(go);
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
        objects[id];
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
