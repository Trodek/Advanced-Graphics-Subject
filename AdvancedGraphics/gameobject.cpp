#include "gameobject.h"
#include "transform.h"
#include "scene.h"
#include <QJsonObject>
#include <QJsonArray>
#include "appmanager.h"
#include "modelrender.h"
#include "light.h"

// All GameObjects start with a transform
GameObject::GameObject()
{
    AddComponent(Component::Type::Transform);
}

GameObject::~GameObject()
{
    for(Component* c : components)
    {
        delete c;
    }
    components.clear();

    for(GameObject* go: children)
    {
        delete go;
    }
    children.clear();
}

const char *GameObject::GetName() const
{
    return name.c_str();
}

void GameObject::SetName(const char *name)
{
    this->name = name;
}

Component *GameObject::GetComponentByType(Component::Type type) const
{
    Component* ret = nullptr;

    for(Component* c : components)
    {
        if(c->GetType() == type)
        {
            ret = c;
            break;
        }
    }

    return  ret;
}

Component *GameObject::GetComponentByID(int id) const
{
    if(id < components.size())
        return components[id];

    return nullptr;
}

int GameObject::NumComponents() const
{
    return components.size();
}

Component* GameObject::AddComponent(Component::Type type)
{
    Component* ret = nullptr;

    switch (type) {
    case Component::Type::Transform:
        if(GetComponentByType(type) == nullptr)
            ret = new Transform();
        break;
    case Component::Type::ModelRenderer:
        if(GetComponentByType(type) == nullptr)
            ret = new ModelRender();
        break;
    case Component::Type::Light:
        if(GetComponentByType(type) == nullptr)
            ret = new Light();
    default:
        break;
    }

    if(ret != nullptr)
    {
        components.push_back(ret);
    }

    return ret;
}

// Removes all components of "type" from the gameobject
void GameObject::RemoveComponent(Component::Type type)
{
    for(std::vector<Component*>::iterator c = components.begin(); c != components.end(); c++)
    {
        if((*c)->GetType() == type)
        {
            delete *c;
            components.erase(c);
        }
    }

}

void GameObject::RemoveComponent(int id)
{
    if(id < components.size() )
    {
        int i = 0;
        for(std::vector<Component*>::iterator c = components.begin(); c != components.end(); c++)
        {
            if(i == id)
            {
                delete *c;
                components.erase(c);
                break;
            }
            i++;
        }
    }
}

GameObject *GameObject::GetChild(int id) const
{
    if(id < children.size())
        return children[id];
    return nullptr;
}

GameObject *GameObject::GetChild(std::string name) const
{
    GameObject* ret = nullptr;
    for(GameObject* go : children)
    {
        if(go->name == name)
        {
            ret = go;
            break;
        }
    }
    return ret;
}

int GameObject::NumChildren() const
{
    return children.size();
}

void GameObject::AddChild(GameObject *go)
{
    if(go != nullptr)
        children.push_back(go);
}

void GameObject::RemoveChild(GameObject *go)
{
    for(std::vector<GameObject*>::iterator c = children.begin(); c != children.end();c++)
    {
        if(go == *c)
        {
            delete *c;
            children.erase(c);
            break;
        }
    }
}

void GameObject::RemoveChild(int id)
{
    if(id < children.size())
    {
        int i = 0;
        for(std::vector<GameObject*>::iterator c = children.begin(); c != children.end();c++)
        {
            if(i == id)
            {
                delete *c;
                children.erase(c);
                break;
            }
            i++;
        }
    }
}

void GameObject::Save(QJsonObject &file) const
{
    file["name"] = name.c_str();
    QJsonArray comp;
    for(std::vector<Component*>::const_iterator c = components.begin(); c != components.end(); c++)
    {
        QJsonObject compObject;
        (*c)->Save(compObject);
        comp.append(compObject);
    }
    file["Components"] = comp;

}

void GameObject::Load(const QJsonObject &file)
{
    if(file.contains("name") && file["name"].isString())
        SetName(file["name"].toString().toUtf8());

    if(file.contains("Components") && file["Components"].isArray())
    {
        QJsonArray compObjects = file["Components"].toArray();
        for(int i = 0; i< compObjects.size();++i)
        {
            QJsonObject comp = compObjects[i].toObject();
            Component::Type type = (Component::Type)comp["type"].toInt();
            Component* c = nullptr;
            if(type == Component::Type::Transform)
                c = GetComponentByType(type);
            else
                c = AddComponent(type);

            c->Load(comp);
        }
    }
}
