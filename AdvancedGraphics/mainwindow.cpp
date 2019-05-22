#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>
#include "transformwidget.h"
#include "scene.h"
#include "gameobject.h"
#include "transform.h"
#include "hierarchy.h"
#include "collapsewidget.h"
#include "gameobject.h"
#include "inspector.h"
#include "scene.h"
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

}
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
