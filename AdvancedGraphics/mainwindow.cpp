#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>
#include "shapedrawerwidget.h"
#include "transformwidget.h"
//Test
#include "scene.h"
#include "gameobject.h"
#include "transform.h"
#include "shaperenderer.h"
#include "shaperendererwidget.h"
#include "hierarchy.h"
#include "collapsewidget.h"
#include "gameobject.h"
#include "inspector.h"
#include "scene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFile file(":/stylesheets/DarkStyle.css");
    if(file.open(QIODevice::ReadOnly)){
        QString contents = file.readAll();
        setStyleSheet(contents);
    }
    ui->setupUi(this);

    // Create Hierarchy & Inspector
    m_Hierarchy = new Hierarchy();
    m_Inspector = new Inspector();

    m_ShapeDrawer = ui->widget;
    m_Trans = m_Inspector->m_TransformWidget;

    connect(m_Trans,SIGNAL(UpdateDrawer()),this,SLOT(Redraw()));
    connect(m_Inspector->m_ShapeRendererWidget,SIGNAL(UpdateDrawer()),this,SLOT(Redraw()));

    //Add the Widget
    ui->dockHierarchy->setWidget(m_Hierarchy);
    ui->dockInspector->setWidget(m_Inspector);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Redraw()
{
    m_ShapeDrawer->update();
}
