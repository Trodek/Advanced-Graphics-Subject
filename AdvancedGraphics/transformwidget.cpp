#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "gameobject.h"
#include "transform.h"
#include "scene.h"
#include <iostream>
#include "appmanager.h"

TransformWidget::TransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    ui->setupUi(this);
    UpdateUIValues();
}

TransformWidget::~TransformWidget()
{
    delete ui;
}

void TransformWidget::UpdateUIValues()
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) SetToZero();
    else {
        Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);

        if(aux == nullptr) SetToZero();
        else {
            ui->Name->setText(go->GetName());

            ui->PosX->setValue(aux->GetPosition().x());
            ui->PosY->setValue(aux->GetPosition().y());
            ui->PosZ->setValue(aux->GetPosition().z());


            ui->ScaleX->setValue(aux->GetScale().x());
            ui->ScaleY->setValue(aux->GetScale().y());
            ui->ScaleZ->setValue(aux->GetScale().z());

            ui->RotX->setValue(aux->GetEulerRotation().x());
            ui->RotY->setValue(aux->GetEulerRotation().y());
            ui->RotZ->setValue(aux->GetEulerRotation().z());

        }

    }
}

void TransformWidget::SetToZero()
{
    ui->Name->setText("");
    ui->PosX->setValue(0);
    ui->PosY->setValue(0);
    ui->PosZ->setValue(0);
    ui->ScaleX->setValue(0);
    ui->ScaleY->setValue(0);
    ui->ScaleZ->setValue(0);
    ui->RotX->setValue(0);
    ui->RotY->setValue(0);
    ui->RotZ->setValue(0);
}

void TransformWidget::on_PosX_valueChanged(double arg1)
{
    double posX = ui->PosX->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetPosition(QVector3D(posX,aux->GetPosition().y(),aux->GetPosition().z()));
}

void TransformWidget::on_PosY_valueChanged(double arg1)
{
    double posY = ui->PosY->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetPosition(QVector3D(aux->GetPosition().x(),posY,aux->GetPosition().z()));
}

void TransformWidget::on_PosZ_valueChanged(double arg1)
{
    double posZ = ui->PosZ->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetPosition(QVector3D(aux->GetPosition().x(),aux->GetPosition().y(),posZ));
}

void TransformWidget::on_ScaleX_valueChanged(double arg1)
{
    double scaleX = ui->ScaleX->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetScale(QVector3D(scaleX,aux->GetScale().y(),aux->GetScale().z()));
}

void TransformWidget::on_ScaleY_valueChanged(double arg1)
{
    double scaleY = ui->ScaleY->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetScale(QVector3D(aux->GetScale().x(),scaleY,aux->GetScale().z()));
}

void TransformWidget::on_ScaleZ_valueChanged(double arg1)
{
    double scaleZ = ui->ScaleZ->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetScale(QVector3D(aux->GetScale().x(),aux->GetScale().y(),scaleZ));
}

void TransformWidget::on_Name_textEdited(const QString &arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();

    if(go == nullptr) return;

    go->SetName(ui->Name->text().toStdString().c_str());

    emit AppManager::Instance()->GetInspector()->UpdateName();
}
