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
    //Update Logic of curr_gameObject Transform
    double posX = ui->PosX->value();
    double posY = ui->PosY->value();
    double scaleX = ui->ScaleX->value();
    double scaleY = ui->ScaleY->value();

    Transform* aux = (Transform*)Scene::Instance()->GetSelectedGameObject()->GetComponentByType(Component::Transform);
    aux->SetPosition(QVector2D(posX,posY));
    aux->SetScale(QVector2D(scaleX,scaleY));

    //Redraw UI

}
void TransformWidget::UpdateUIValues()
{
    Transform* aux = (Transform*)Scene::Instance()->GetSelectedGameObject()->GetComponentByType(Component::Transform);

    ui->PosX->setValue(aux->GetPosition().y());
    ui->PosY->setValue(aux->GetPosition().y());
    ui->ScaleX->setValue(aux->GetScale().x());
    ui->ScaleY->setValue(aux->GetPosition().y());

}

void TransformWidget::on_PosX_valueChanged(double arg1)
{
    TransformModified();
}

void TransformWidget::on_PosY_valueChanged(double arg1)
{
    TransformModified();
}

void TransformWidget::on_ScaleX_valueChanged(double arg1)
{
    TransformModified();
}

void TransformWidget::on_ScaleY_valueChanged(double arg1)
{
    TransformModified();
}
