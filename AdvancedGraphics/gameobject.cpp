#include "gameobject.h"
#include "transform.h"
#include "shaperenderer.h"
#include "scene.h"

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
        ret = new Transform();
        break;
    case Component::Type::ShapeRender:
        ret = new ShapeRenderer();
        break;
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
void GameObject::SetBaseInfo()
{
    QString s = QString::number( Scene::Instance()->NumGameObjects());
    this->SetName(s.toLocal8Bit());
    ShapeRenderer *sr = (ShapeRenderer*)this->AddComponent(Component::Type::ShapeRender);
    Transform *t = (Transform*)this->GetComponentByType(Component::Type::Transform);
    sr->SetShape(ShapeRenderer::Shape::Circle);
    sr->SetLineStyle(Qt::PenStyle::SolidLine);
    sr->SetLineColor(QColor(51,241,34));
    sr->SetBrushStyle(Qt::BrushStyle::SolidPattern);
    sr->SetShapeColor(QColor(100,50,69));
    sr->SetLineSize(2);
    sr->SetSize(QVector2D(90,60));
    t->SetPosition(QVector2D(0,0));
    Scene::Instance()->AddGameObject(this);
}
