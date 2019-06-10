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
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QString>
#include "resourcemanager.h"
#include "model.h"
#include "shaderprogram.h"
#include "texture.h"

#define WORKPATH "../Resources"

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
    AppManager::Instance()->SetMainWindow(this);

    // Create Hierarchy & Inspector
    m_Hierarchy = new Hierarchy();
    AppManager::Instance()->SetHierarchy(m_Hierarchy);
    m_Inspector = new Inspector();
    AppManager::Instance()->SetInspector(m_Inspector);
    m_OpenGLWidget = new OpenGLWidget();
    AppManager::Instance()->SetOpenGLWidget(m_OpenGLWidget);

    //Add the Widget
    ui->dockHierarchy->setWidget(m_Hierarchy);
    ui->dockInspector->setWidget(m_Inspector);
    ui->OpenGLLoc->addWidget(m_OpenGLWidget);
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

void MainWindow::on_actionSave_Scene_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Scene"), WORKPATH, tr("Scene File (*.scene);;All Files(*)"));

    QFile saveFile(fileName);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file");
        return;
    }

    QJsonObject sceneObject;
    Scene::Instance()->SaveScene(sceneObject);
    QJsonDocument saveDoc(sceneObject);
    saveFile.write(saveDoc.toJson());
}

void MainWindow::on_actionLoad_Scene_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Scene"), WORKPATH, tr("Scene File (*.scene);;All Files(*)"));

    QFile loadFile(fileName);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open load file");
        return;
    }

    QByteArray sceneData(loadFile.readAll());

    QJsonDocument sceneDoc(QJsonDocument::fromJson(sceneData));
    Scene::Instance()->LoadScene(sceneDoc.object());

}

void MainWindow::on_actionNew_Scene_triggered()
{
    AppManager::Instance()->GetHierarchy()->NewScene();
    Scene::Instance()->NewScene();
    emit AppManager::Instance()->GetHierarchy()->UpdateInspector();
}

void MainWindow::on_actionLoad_Texture_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Texture"), WORKPATH, tr("Texture (*.jpg);Texture (*.png);All Files(*)"));

    QDir path("."); //create relative path

    Texture* tex = ResourceManager::Instance()->CreateTexture();
    tex->loadFromFile(path.relativeFilePath(fileName));
    emit AppManager::Instance()->GetHierarchy()->UpdateInspector();
}

void MainWindow::on_actionLoad_Model_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Model"), WORKPATH, tr("Model (*.obj);;All Files(*)"));

    QDir path("."); //create relative path

    Model* model = ResourceManager::Instance()->CreateModel();
    model->loadModel(path.relativeFilePath(fileName).toStdString());
    emit AppManager::Instance()->GetHierarchy()->UpdateInspector();
}

void MainWindow::on_actionLoad_Shader_triggered()
{
    QString vertPath = QFileDialog::getOpenFileName(this, tr("Load Vertex Shader"), WORKPATH, tr("Model (*.vs);;All Files(*)"));
    QString fragPath = QFileDialog::getOpenFileName(this, tr("Load Fragment Shader"), WORKPATH, tr("Model (*.fs);;All Files(*)"));

    QDir path("."); //create relative path

    ShaderProgram* shader = ResourceManager::Instance()->CreateShaderProgram();
    shader->SetShaders(path.relativeFilePath(vertPath),path.relativeFilePath(fragPath));
    emit AppManager::Instance()->GetHierarchy()->UpdateInspector();
}
