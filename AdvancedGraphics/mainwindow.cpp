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
#include  "ui_aboutgl.h"
#include "appmanager.h"
#include "openglwidget.h"

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
    m_OpenGLWidget = new OpenGLWidget();

    m_ShapeDrawer = ui->widget;
    m_Trans = m_Inspector->m_TransformWidget;

    connect(m_Trans,SIGNAL(UpdateDrawer()),this,SLOT(Redraw()));
    connect(m_Inspector->m_ShapeRendererWidget,SIGNAL(UpdateDrawer()),this,SLOT(Redraw()));
    connect(m_Hierarchy,SIGNAL(GameObjectChanged()),m_Trans,SLOT(UpdateUIValues()));
    connect(m_Hierarchy,SIGNAL(GameObjectChanged()),m_Inspector->m_ShapeRendererWidget,SLOT(UpdateUIValues()));
    connect(m_Trans,SIGNAL(UpdateHierarchy()),m_Hierarchy,SLOT(UpdateHierachyNames()));

    connect(ui->actionAboutOpenGL,SIGNAL(triggered()),this,SLOT(OpenaboutGL()));
    //Add the Widget
    ui->dockHierarchy->setWidget(m_Hierarchy);
    ui->dockInspector->setWidget(m_Inspector);
    //App Manager SetUp
    AppManager::Instance()->SetHierarchy(m_Hierarchy);
    AppManager::Instance()->SetInspector(m_Inspector);
    AppManager::Instance()->SetOpenGLWidget(m_OpenGLWidget);
    AppManager::Instance()->SetMainWindow(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Redraw()
{
    m_ShapeDrawer->update();
}
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
/*
void MainWindow::OpenaboutGL()
{
    QDialog dialog;
    Ui::AboutGL m_about;
    m_about.setupUi(&dialog);
    m_about.textBrowser->setText(ui->openGLWidget->getOpenGLinfo());
    dialog.exec();
}*/
