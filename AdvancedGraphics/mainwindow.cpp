#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFile file(":/stylesheets/DarkStyle.css");
    if(file.open(QIODevice::ReadOnly)){
        QString contents = file.readAll();
        setStyleSheet(contents);
        std::cout << "simon la xupa";
    }
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
