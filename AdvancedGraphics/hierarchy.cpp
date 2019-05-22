#include "mainwindow.h"
#include "hierarchy.h"
#include "scene.h"
#include "ui_hierarchy.h"
#include "gameobject.h"
#include "hierarchyobject.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HierarchyDock)
{
    ui->setupUi(this);
    //Connects
    connect(ui->AddObject,SIGNAL(clicked()),this,SLOT(AddGameObject()));
    connect(ui->DestroyObject, SIGNAL(clicked()), this, SLOT(DeleteGameObject()));

}

Hierarchy::~Hierarchy()
{
    delete ui;
}
void Hierarchy::AddGameObject()
{
    //CreateGameObject and Add it to the listWidget
    GameObject* newGO = new GameObject();
    QString s =  "GameObject ";
    s += QString::number(Scene::Instance()->NumGameObjects());
    newGO->SetName(s.toLocal8Bit());
    Scene::Instance()->AddGameObject(newGO);

     HierarchyObject* objectUI = new HierarchyObject(newGO);
     ui->verticalLayout->insertWidget(ui->verticalLayout->count()-1, objectUI);

    Scene::Instance()->SetSelectedGameObject(newGO);
    //UpdateUI
    emit GameObjectChanged();


}
void Hierarchy::DeleteGameObject()
{
    //DeleteGameObject
    Scene::Instance()->RemoveGameObject(Scene::Instance()->GetSelectedGameObject());
    for(int i = 0; i < Scene::Instance()->NumGameObjects();i++)
    {
    }

    //Stablish another active GO
    if(Scene::Instance()->NumGameObjects() > 0 )
    {
        Scene::Instance()->SetSelectedGameObject(0);
        //Removed GameObject
    }
    emit GameObjectChanged();
    //UpdateCanvas
}

void Hierarchy::SelectGameObject()
{

}

void Hierarchy::UpdateHierachyNames()
{

}
