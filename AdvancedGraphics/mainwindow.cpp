#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>

#include "ui_aboutgl.h"

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

    connect(ui->actionAbout_OpenGL, SIGNAL(triggered()), this, SLOT(OpenAboutGL()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenAboutGL()
{
    QDialog dialog;
    Ui::AboutGL about;
    about.setupUi(&dialog);
    about.textBrowser->setText(ui->openGLWidget->getOpenGLinfo());
    dialog.exec();
}


