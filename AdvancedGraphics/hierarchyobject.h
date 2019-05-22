#ifndef HIERARCHYOBJECT_H
#define HIERARCHYOBJECT_H

#include <QWidget>

namespace Ui {
class HierarchyObject;
}

class GameObject;

class HierarchyObject : public QWidget
{
    Q_OBJECT

public:
    explicit HierarchyObject(GameObject* go, QWidget *parent = nullptr);
    ~HierarchyObject();

    GameObject* AssignedGO()const;

public slots:
    void UpdateName();

private slots:
    void OnObjectClicked();

private:
    Ui::HierarchyObject *ui;

    GameObject* go;
};

#endif // HIERARCHYOBJECT_H
