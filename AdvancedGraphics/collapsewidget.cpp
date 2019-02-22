#include "collapsewidget.h"
#include "ui_collapsewidget.h"

CollapseWidget::CollapseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollapseWidget)
{
    ui->setupUi(this);
}

CollapseWidget::~CollapseWidget()
{
    delete ui;
}
