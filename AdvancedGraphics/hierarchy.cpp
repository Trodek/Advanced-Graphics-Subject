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
    ui->verticalLayout_3->addWidget(objectUI);

    Scene::Instance()->SetSelectedGameObject(newGO);
    //UpdateUI
    emit UpdateInspector();


}
void Hierarchy::DeleteGameObject()
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();

    //Remove hierarchy object
    if(go != nullptr)
    {
        for(int i = 0; i < ui->verticalLayout_3->count();++i)
        {
            QWidget* widget = ui->verticalLayout_3->itemAt(i)->widget();
            HierarchyObject* obj = (HierarchyObject*)widget;
            if(obj->AssignedGO() == go)
            {
                ui->verticalLayout_3->removeItem(ui->verticalLayout_3->itemAt(i));
                delete widget;
                break;
            }
        }
        Scene::Instance()->RemoveGameObject(go);
    }

    emit UpdateInspector();
}

