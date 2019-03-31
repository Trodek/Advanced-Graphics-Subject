#include "mainwindow.h"
#include "hierarchy.h"
#include "scene.h"
#include "ui_hierarchy.h"
#include "gameobject.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HierarchyDock)
{
    ui->setupUi(this);
    //Connects
    connect(ui->AddShape, SIGNAL(clicked()), this, SLOT(AddGameObject()));
    connect(ui->DestroyShape, SIGNAL(clicked()), this, SLOT(DeleteGameObject()));
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SelectGameObject()));

}

Hierarchy::~Hierarchy()
{
    delete ui;
}
void Hierarchy::AddGameObject()
{
    //CreateGameObject and Add it to the listWidget
    GameObject* newShape = new GameObject();
    newShape->SetBaseInfo();
    ui->listWidget->addItem(newShape->GetName());
    //
    Scene::Instance()->SetSelectedGameObject(Scene::Instance()->NumGameObjects()-1);
    //UpdateUI
    emit GameObjectChanged();


}
void Hierarchy::DeleteGameObject()
{
    //DeleteGameObject
    Scene::Instance()->RemoveGameObject(Scene::Instance()->GetSelectedGameObject());
    ui->listWidget->clear();
   for(int i = 0; i < Scene::Instance()->NumGameObjects();i++)
    {
        ui->listWidget->addItem(Scene::Instance()->GetGameObject(i)->GetName());
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
    for (int i = 0; i < Scene::Instance()->NumGameObjects();i++)
    {
        if ( Scene::Instance()->GetGameObject(i)->GetName() == ui->listWidget->currentItem()->text())
        {
           Scene::Instance()->SetSelectedGameObject(i);
           emit GameObjectChanged();
        }
    }
}
