#include "shaperendererwidget.h"
#include "ui_shaperendererwidget.h"

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
