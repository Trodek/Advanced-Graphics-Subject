#include "hierarchyobject.h"
#include "ui_hierarchyobject.h"
#include "gameobject.h"
#include "scene.h"

HierarchyObject::HierarchyObject(GameObject* go, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HierarchyObject)
{
    ui->setupUi(this);
    this->go = go;
    ui->entityName->setText(go->GetName());
}

HierarchyObject::~HierarchyObject()
{
    delete ui;
}

void HierarchyObject::OnObjectClicked()
{
    Scene::Instance()->SetSelectedGameObject(go);
}
