#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "gameobject.h"
#include "transform.h"
#include "scene.h"
#include <iostream>

TransformWidget::TransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    ui->setupUi(this);
}

TransformWidget::~TransformWidget()
{
    delete ui;
}

void TransformWidget::TransformModified()
{
    //Redraw UI
    emit UpdateDrawer();

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
            ui->ScaleX->setValue(aux->GetScale().x());
            ui->ScaleY->setValue(aux->GetScale().y());
        }

    }
}

void TransformWidget::SetToZero()
{
    ui->Name->setText("");
    ui->PosX->setValue(0);
    ui->PosY->setValue(0);
    ui->ScaleX->setValue(0);
    ui->ScaleY->setValue(0);
}

void TransformWidget::on_PosX_valueChanged(double arg1)
{
    double posX = ui->PosX->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetPosition(QVector2D(posX,aux->GetPosition().y()));

    TransformModified();
}

void TransformWidget::on_PosY_valueChanged(double arg1)
{
    double posY = ui->PosY->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetPosition(QVector2D(aux->GetPosition().x(),posY));

    TransformModified();
}

void TransformWidget::on_ScaleX_valueChanged(double arg1)
{
    double scaleX = ui->ScaleX->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetScale(QVector2D(scaleX,aux->GetScale().y()));

    TransformModified();
}

void TransformWidget::on_ScaleY_valueChanged(double arg1)
{
    double scaleY = ui->ScaleY->value();

    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    Transform* aux = (Transform*)go->GetComponentByType(Component::Transform);
    if(aux == nullptr) return;

    aux->SetScale(QVector2D(aux->GetScale().x(),scaleY));

    TransformModified();
}

void TransformWidget::on_Name_textEdited(const QString &arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();

    if(go == nullptr) return;

    go->SetName(ui->Name->text().toStdString().c_str());

    emit UpdateHierarchy();
}
