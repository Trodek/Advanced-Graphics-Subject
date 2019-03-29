#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>
//Test
#include "scene.h"
#include "gameobject.h"
#include "transform.h"

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

    //Add the Widget
    ui->dockHierarchy->setWidget(m_Hierarchy);
    ui->dockInspector->setWidget(m_Inspector);

    std::cout <<"Num objects: "<< Scene::Instance()->NumGameObjects() << std::endl;
    GameObject* test = Scene::Instance()->GetGameObject(0);
    std::cout << "Object components: " << test->NumComponents() << std::endl;
    Transform* t = (Transform*)test->GetComponentByType(Component::Type::Transform);
    std::cout << "Transform Pos: " << t->GetPosition().x() << " " << t->GetPosition().y() << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
