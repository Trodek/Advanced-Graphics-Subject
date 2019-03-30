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
   // shape_comp = static_cast<ShapeRenderer*>(my_GO->GetComponentByType(Component::ShapeRender));
}

ShapeRendererWidget::~ShapeRendererWidget()
{
    delete ui;
}

void ShapeRendererWidget::UpdateUIOnShapeType()
{
    if(shape_comp->GetShape() == ShapeRenderer::Shape::Circle)
    {
        //Put Radius
        //Update ComboBox
        ui->ShapeComboBOx->clear();
        QStringList list = (QStringList()<<"Circle"<<"Rectangle");
        ui->ShapeComboBOx->addItems(list);
    }
     else if(shape_comp->GetShape() == ShapeRenderer::Shape::Rectangle)
    {
        //Put Height & Width
        //Update ComboBox
        ui->ShapeComboBOx->clear();
        QStringList list = (QStringList()<<"Rectangle"<<"Circle");
        ui->ShapeComboBOx->addItems(list);

    }
}
void ShapeRendererWidget:: UpdateUIValues()
{
    //Update First Combo Box
    UpdateUIOnShapeType();

}
void ShapeRendererWidget::UpdateShapeDimensions(int x,int y)
{
    shape_comp->SetSize(QVector2D(x,y));
}
void ShapeRendererWidget::UpdateShapeColor(int r,int g,int b)
{
shape_comp->SetShapeColor(QColor(r,g,b));
}
void ShapeRendererWidget::UpdateLineColor(int r, int g, int b)
{
shape_comp->SetLineColor(QColor(r,g,b));
}
void ShapeRendererWidget::UpdateLineSize(int size)
{
    shape_comp->SetLineSize(size);
}
void ShapeRendererWidget::UpdateLineStyle(Qt::PenStyle s)
{
    shape_comp->SetLineStyle(s);
}





