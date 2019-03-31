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
    connect(ui->listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(SelectGameObject()));

}

Hierarchy::~Hierarchy()
{
    delete ui;
}
void Hierarchy::AddGameObject()
{
    //CreateGameObject and Add it to the listWidget
    GameObject* newShape = new GameObject();
    ui->listWidget->addItem(newShape->GetName());
    //
    Scene::Instance()->SetSelectedGameObject(1);
    //UpdateUI

}
void Hierarchy::DeleteGameObject()
{
    //DeleteGameObject
    //Stablish another active GO
    //UpdateCanvas
}
void Hierarchy::SelectGameObject()
{
    for (int i = 0; i < Scene::Instance()->NumGameObjects();i++)
    {
        if ( Scene::Instance()->GetGameObject(i)->GetName() == ui->listWidget->currentItem()->text())
        {
           Scene::Instance()->SetSelectedGameObject(i);
        }
    }
}
