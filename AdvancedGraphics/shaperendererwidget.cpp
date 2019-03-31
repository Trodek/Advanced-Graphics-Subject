#include "shaperendererwidget.h"
#include "ui_shaperendererwidget.h"
#include "scene.h"
#include "shaperenderer.h"
#include "gameobject.h"

ShapeRendererWidget::ShapeRendererWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeRendererWidget)
{
    ui->setupUi(this);
}

ShapeRendererWidget::~ShapeRendererWidget()
{
    delete ui;
}

void ShapeRendererWidget:: UpdateUIValues()
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) SetToZero();
    else {

        ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);

        if(aux == nullptr) SetToZero();
        else {
            ui->ShapeComboBox->setCurrentIndex(aux->GetShape());
            ui->Shape_w->setValue(aux->GetSize().x());
            ui->Shape_h->setValue(aux->GetSize().y());
            int r,g,b;
            aux->GetShapeColor().getRgb(&r,&g,&b);
            ui->FillRedValue->setValue(r);
            ui->FillBlueValue->setValue(b);
            ui->FillGreenValue->setValue(g);
            aux->GetLineColor().getRgb(&r,&g,&b);
            ui->StrokeRedValue->setValue(r);
            ui->StrokeGreenValue->setValue(g);
            ui->StrokeBlueValue->setValue(b);
            ui->StrokeTypeComboBox->setCurrentIndex(aux->GetLineStyle());
            ui->StrokeThicknessValue->setValue(aux->GetLineSize());
        }

    }

}

void ShapeRendererWidget::ShapeUpdated()
{
    emit UpdateDrawer();
}

void ShapeRendererWidget::SetToZero()
{
    ui->ShapeComboBox->setCurrentIndex(0);
    ui->Shape_w->setValue(0);
    ui->Shape_h->setValue(0);

    ui->FillRedValue->setValue(0);
    ui->FillBlueValue->setValue(0);
    ui->FillGreenValue->setValue(0);

    ui->StrokeRedValue->setValue(0);
    ui->StrokeGreenValue->setValue(0);
    ui->StrokeBlueValue->setValue(0);
    ui->StrokeTypeComboBox->setCurrentIndex(0);
    ui->StrokeThicknessValue->setValue(0);
}

void ShapeRendererWidget::on_ShapeComboBox_currentIndexChanged(int index)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    aux->SetShape((ShapeRenderer::Shape)index);

    ShapeUpdated();
}

void ShapeRendererWidget::on_Shape_w_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    aux->SetSize(QVector2D(arg1,aux->GetSize().y()));

    ShapeUpdated();
}

void ShapeRendererWidget::on_Shape_h_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    aux->SetSize(QVector2D(aux->GetSize().x(),arg1));

    ShapeUpdated();
}

void ShapeRendererWidget::on_FillRedValue_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    QColor c = aux->GetShapeColor();
    c.setRed(arg1);

    aux->SetShapeColor(c);

    ShapeUpdated();
}

void ShapeRendererWidget::on_FillGreenValue_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    QColor c = aux->GetShapeColor();
    c.setGreen(arg1);

    aux->SetShapeColor(c);

    ShapeUpdated();
}

void ShapeRendererWidget::on_FillBlueValue_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    QColor c = aux->GetShapeColor();
    c.setBlue(arg1);

    aux->SetShapeColor(c);

    ShapeUpdated();
}

void ShapeRendererWidget::on_StrokeRedValue_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    QColor c = aux->GetShapeColor();
    c.setRed(arg1);

    aux->SetLineColor(c);

    ShapeUpdated();
}

void ShapeRendererWidget::on_StrokeGreenValue_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    QColor c = aux->GetShapeColor();
    c.setGreen(arg1);

    aux->SetLineColor(c);

    ShapeUpdated();
}

void ShapeRendererWidget::on_StrokeBlueValue_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    QColor c = aux->GetShapeColor();
    c.setBlue(arg1);

    aux->SetLineColor(c);

    ShapeUpdated();
}

void ShapeRendererWidget::on_StrokeThicknessValue_valueChanged(int arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    aux->SetLineSize(arg1);

    ShapeUpdated();
}

void ShapeRendererWidget::on_StrokeTypeComboBox_currentIndexChanged(int index)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go == nullptr) return;
    ShapeRenderer* aux = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
    if(aux == nullptr) return;

    aux->SetLineStyle((Qt::PenStyle)index);

    ShapeUpdated();
}
