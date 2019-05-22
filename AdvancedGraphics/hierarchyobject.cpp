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

    connect(ui->entityName,SIGNAL(clicked()),this,SLOT(OnObjectClicked()));
}

HierarchyObject::~HierarchyObject()
{
    delete ui;
}

GameObject *HierarchyObject::AssignedGO() const
{
    return go;
}

void HierarchyObject::UpdateName()
{
    ui->entityName->setText(go->GetName());
}

void HierarchyObject::OnObjectClicked()
{
    Scene::Instance()->SetSelectedGameObject(go);
}
