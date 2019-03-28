#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

#include "component.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();

    const char* GetName() const;
    void SetName(const char* name);

    // Components
    Component* GetComponentByType(Component::Type type) const;
    Component* GetComponentByID(int id) const;
    int NumComponents() const;

    Component* AddComponent(Component::Type type);
    void RemoveComponent(Component::Type type);
    void RemoveComponent(int id);

    // Children
    GameObject* GetChild(int id)const;
    GameObject* GetChild(std::string name)const;
    int NumChildren()const;

    void AddChild(GameObject* go);
    void RemoveChild(GameObject* go);
    void RemoveChild(int id);


private:
    std::string name;

    std::vector<Component*> components;
    std::vector<GameObject*> children;
};

#endif // GAMEOBJECT_H
