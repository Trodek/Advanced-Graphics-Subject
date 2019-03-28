#ifndef SCENE_H
#define SCENE_H

#include <vector>

class GameObject;

class Scene
{
public:
    ~Scene();

    static Scene* Instance();
    GameObject* GetGameObject(int id) const;
    int NumGameObjects() const;

    void AddGameObject(GameObject* go);
    void RemoveGameObject(int id);
    void RemoveGameObject(GameObject* go);

private:
    Scene();

private:
    static Scene* instance;
    std::vector<GameObject*> objects;
};

#endif // SCENE_H
