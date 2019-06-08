#include "openglwidget.h"
#include <iostream>
#include "resourcemanager.h"

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
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
void OpenGLWidget::PaintTriangleExample()
{
    //Shader Program creation and setup
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader1_vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag");
    program.link();
    program.bind();
    //---------------------------------
}
