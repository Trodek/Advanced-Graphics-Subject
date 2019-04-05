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

QString OpenGLWidget::getOpenGLinfo()
{
    QString info;
    makeCurrent();
    /*info += "OpenGL version:";
    info += "\n";
    info += glGetString(GL_VERSION);
    info += "\n\n";
    info += "OpenGL renderer:";
    info += "\n";
    info += glGetString(GL_RENDERER);
    info += "\n\n";
    info += "OpenGL vendor:";
    info += "\n";
    info += glGetString(GL_VENDOR);
    info += "\n\n";
    info += "OpenGL &St version:";
    info += "\n";
    info += glGetString(GL_SNADING_LANGUAGE_VERSION);
    info += "\n\n";
    info += "OpenGL extensions:";
    info += "\n";*/
    /*« std::endl; GLint num_extensions; glGetIntegerv(GLNOM_EXTENSIONS, denum_extensions); for (int i = El; i < num_extensions; ++1) const unsigned char *str = glGetStringi(GL_EXTENSIONS, GLuint(i)); std::cout « str « " "; std::cout « std::endl;
    // Information about the surface std::cout « contextO->formatO. std::cout « context()->format(). std::cout « context()->format(). std::cout « context()->format(). std::cout cc context()->format().
    format redBufferSize() « std::endl; greenBufferSize() « std::endt; blueBufferSize() « std::endl; alphaBufferSize() <c std::endl; depthBufferSize() << std::endl;
    */
    return info;
}

void OpenGLWidget::finalizeGL()
{
std::cout << "finalizeGL()"<< std::endl;
}

