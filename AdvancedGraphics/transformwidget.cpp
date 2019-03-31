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
    UpdateUIValues();
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
    Transform* aux = (Transform*)Scene::Instance()->GetSelectedGameObject()->GetComponentByType(Component::Transform);

    if(aux == nullptr) return;

    ui->PosX->setValue(aux->GetPosition().x());
    ui->PosY->setValue(aux->GetPosition().y());
    ui->ScaleX->setValue(aux->GetScale().x());
    ui->ScaleY->setValue(aux->GetScale().y());

}

void TransformWidget::on_PosX_valueChanged(double arg1)
{
    double posX = ui->PosX->value();

    Transform* aux = (Transform*)Scene::Instance()->GetSelectedGameObject()->GetComponentByType(Component::Transform);

    if(aux == nullptr) return;

    aux->SetPosition(QVector2D(posX,aux->GetPosition().y()));

    TransformModified();
}

void TransformWidget::on_PosY_valueChanged(double arg1)
{
    double posY = ui->PosY->value();

    Transform* aux = (Transform*)Scene::Instance()->GetSelectedGameObject()->GetComponentByType(Component::Transform);

    if(aux == nullptr) return;

    aux->SetPosition(QVector2D(aux->GetPosition().x(),posY));

    TransformModified();
}

void TransformWidget::on_ScaleX_valueChanged(double arg1)
{
    double scaleX = ui->ScaleX->value();

    Transform* aux = (Transform*)Scene::Instance()->GetSelectedGameObject()->GetComponentByType(Component::Transform);

    if(aux == nullptr) return;

    aux->SetScale(QVector2D(scaleX,aux->GetScale().y()));

    TransformModified();
}

void TransformWidget::on_ScaleY_valueChanged(double arg1)
{
    double scaleY = ui->ScaleY->value();

    Transform* aux = (Transform*)Scene::Instance()->GetSelectedGameObject()->GetComponentByType(Component::Transform);

    if(aux == nullptr) return;

    aux->SetScale(QVector2D(aux->GetScale().x(),scaleY));

    TransformModified();
}
