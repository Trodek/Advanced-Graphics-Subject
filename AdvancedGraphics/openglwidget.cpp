#include "openglwidget.h"
#include <iostream>

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    finalizeGL();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    connect(context(),SIGNAL(aboutToBeDestroyed()),this,SLOT(finalizeGL()));
}

void OpenGLWidget::paintGL()
{

}

void OpenGLWidget::resizeGL(int w, int h)
{

}

void OpenGLWidget::finalizeGL()
{

}
