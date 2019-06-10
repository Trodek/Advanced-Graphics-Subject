#include "openglwidget.h"
#include <iostream>
#include "resourcemanager.h"
#include "render.h"
#include <QTimer>
#include <QtMath>
#include "model.h"
#include "transform.h"
#include "modelrender.h"
#include "shaderprogram.h"
#include "gameobject.h"
#include "scene.h"

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));

    drawTimer = new QTimer(this);
    connect(drawTimer,SIGNAL(timeout()),this,SLOT(paintGL()));
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

    Render::Instance()->GetFuncs()->initializeOpenGLFunctions();
    ResourceManager::Instance()->CreateSphere();
    ResourceManager::Instance()->CreateQuad();
    InitTriangle();
}

void OpenGLWidget::paintGL()
{
    MakeCurrent();
    glClearColor(0.9f,0.85f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawScene();
}

void OpenGLWidget::InitTriangle()
{
    triProgram = ResourceManager::Instance()->CreateShaderProgram();
    triProgram->name = "TriShader";
    triProgram->SetShaders("../Resources/Shaders/tri.vs","../Resources/Shaders/tri.fs");

    QVector3D vertices[] = {
        QVector3D(-0.5f,-0.5f,0.0f), QVector3D(1.0f,0.0f,0.0f),
        QVector3D(0.5f,-0.5f,0.0f), QVector3D(0.0f,1.0f,0.0f),
        QVector3D(0.0f,0.5f,0.0f), QVector3D(0.0f,0.0f,1.0f)
    };

    const GLint compCount = 3;
    const int offset0 = 0;
    const int offset1 = sizeof(QVector3D);

    VertexFormat format;
    format.SetVertexAttribute(0,offset0,compCount);
    format.SetVertexAttribute(1,offset1,compCount);

    triangle = ResourceManager::Instance()->CreateModel();
    triangle->name = "Triangle";
    triangle->addMesh(format,vertices,6*sizeof(QVector3D));
}

void OpenGLWidget::resizeGL(int w, int h)
{
    CalculateProjection(w/h,45.0f,0.1f,100.0f);
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

    /*if(triProgram->shaderProgram.bind())
    {
        triangle->DrawMeshes();
        triProgram->shaderProgram.release();
    }*/

    std::vector<GameObject*> objects = Scene::Instance()->GetObjectsToDraw();

    for(GameObject* go : objects)
    {
        //get the needed components to render the object
        Transform* trans = (Transform*)go->GetComponentByType(Component::Type::Transform);
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);

        //bind the shader
        ShaderProgram* shader = mr->GetShaderProgram();

        if(shader == nullptr || mr->GetModel() == nullptr) continue;

        if(shader->shaderProgram.bind())
        {
            ///common properties
            //shader->shaderProgram.setUniformValue("projectionMatirx",projection);
            //shader->shaderProgram.setUniformValue("worldViewMatrix",trans->GetTransformMatrix()); //mult by view when camera done

            //draw the model
            mr->GetModel()->DrawMeshes();

            shader->shaderProgram.release();
        }
    }
}

void OpenGLWidget::CalculateProjection(float aspect, float fovy, float nearPlane, float farPlane)
{
    projection.setToIdentity();

    float f = 1/qTan(fovy/2);

    QVector4D row0 = {f/qDegreesToRadians(aspect),0,0,0};
    QVector4D row1 = {0,f,0,0};
    QVector4D row2 = {0,0,(farPlane+nearPlane)/(nearPlane-farPlane),(2*nearPlane*farPlane)/(nearPlane-farPlane)};
    QVector4D row3 = {0,0,-1,0};

    projection.setRow(0,row0);
    projection.setRow(1,row1);
    projection.setRow(2,row2);
    projection.setRow(3,row3);

}
