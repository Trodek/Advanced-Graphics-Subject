#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>
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

    int a = Scene::Instance()->NumGameObjects();
    std::cout << a;
}

MainWindow::~MainWindow()
{
    delete ui;
}
