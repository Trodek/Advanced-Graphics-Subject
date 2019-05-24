#include "inspector.h"
#include "ui_inspector.h"
#include "transformwidget.h"
#include "gameobject.h"
#include "scene.h"
#include "appmanager.h"
#include "component.h"

Inspector::Inspector(QWidget *parent) :
    QWidget(parent), ui(new Ui::Inspector()){

    ui->setupUi(this);
    connect(AppManager::Instance()->GetHierarchy(),SIGNAL(UpdateInspector()),this,SLOT(OnSelectedGoChange()));

}

Inspector::~Inspector()
{
}

void Inspector::OnSelectedGoChange()
{
    //Remove Current inspector components
    for(int i = 0; i < ui->ComponentList->count();++i)
    {
        QWidget* widget = ui->ComponentList->itemAt(i)->widget();
        ui->ComponentList->removeItem(ui->ComponentList->itemAt(i));
        delete widget;
    }

    //Add Components the object has
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    for(int i = 0; i < go->NumComponents(); ++i)
    {
        AddComponentUI(go->GetComponentByID(i)->GetType());
    }

}

void Inspector::AddComponentUI(Component::Type type)
{
    switch (type)
    {
    case Component::Type::Transform:
    {
        TransformWidget* trans = new TransformWidget();
        ui->ComponentList->addWidget(trans);
        break;
    }
    default:
        break;
    }
}

void Inspector::on_AddComponent_clicked()
{
    int index = ui->AddComponentCombo->currentIndex();
    Component::Type comp = (Component::Type)index;

    GameObject* curr_go = Scene::Instance()->GetSelectedGameObject();
    Component* added = curr_go->AddComponent(comp);

    if(added != nullptr)
        AddComponentUI(comp);
}
