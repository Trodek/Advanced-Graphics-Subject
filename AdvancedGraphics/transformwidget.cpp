#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "gameobject.h"
#include "transform.h"

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

    //ModifyTransform
}
void TransformWidget::UpdateUIValues(GameObject *new_GO)
{
    Transform* aux = (Transform*)new_GO->GetComponentByType(Component::Transform);


    ui->PosX->setValue(aux->GetPosition().y());
    ui->PosY->setValue(aux->GetPosition().y());
    ui->ScaleX->setValue(aux->GetScale().x());
    ui->ScaleY->setValue(aux->GetPosition().y());

}
