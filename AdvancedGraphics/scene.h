#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QJsonObject>

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
    void NewScene();

    GameObject* GetSelectedGameObject() const;
    void SetSelectedGameObject(GameObject* go);
    std::vector<GameObject*> GetObjectsToDraw()const;

    void SaveScene(QJsonObject& file) const;
    void LoadScene(const QJsonObject& file);

private:
    Scene();

private:
    static Scene* instance;
    std::vector<GameObject*> objects;

     GameObject* selected= nullptr;
};

#endif // SCENE_H
