#include "openglwidget.h"
#include <iostream>
#include "resourcemanager.h"
#include "render.h"
#include <QTimer>

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));

    drawTimer = new QTimer(this);
    connect(drawTimer,SIGNAL(timeout()),this,SLOT(DrawScene()));
    drawTimer->start(16);
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    finalizeGL();
}

void OpenGLWidget::MakeCurrent()
{
    makeCurrent();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    connect(context(),SIGNAL(aboutToBeDestroyed()),this,SLOT(finalizeGL()));
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.9f,0.85f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    Render::Instance()->CalculateProjection(w/h,45.0f,0.1f,100.0f);
}
QImage OpenGLWidget::getScreenshot()
{
    makeCurrent();
    return grabFramebuffer();
}

void OpenGLWidget::finalizeGL()
{
    std::cout << "finalizeGL()"<< std::endl;
    ResourceManager::Instance()->ClearResources();
}

void OpenGLWidget::DrawScene()
{
    MakeCurrent();
    if(create_shapes)
    {
        Render::Instance()->GetFuncs()->initializeOpenGLFunctions();
        create_shapes = false;
        ResourceManager::Instance()->CreateSphere();
    }
    Render::Instance()->DrawScene();
}
