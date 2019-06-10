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
#include <QMatrix4x4>
#include "input.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include "MathGeoLib.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

QMatrix4x4 MatGeoLibToQt(float4x4 MGLmat)
{
    QMatrix4x4 mat;
    mat.setRow(0, QVector4D(MGLmat[0][0],MGLmat[0][1],MGLmat[0][2],MGLmat[0][3]));
    mat.setRow(1, QVector4D(MGLmat[1][0],MGLmat[1][1],MGLmat[1][2],MGLmat[1][3]));
    mat.setRow(2, QVector4D(MGLmat[2][0],MGLmat[2][1],MGLmat[2][2],MGLmat[2][3]));
    mat.setRow(3, QVector4D(MGLmat[3][0],MGLmat[3][1],MGLmat[3][2],MGLmat[3][3]));
    return mat;
}

QMatrix4x4 GLMToQt(glm::mat4x4 GLMmat)
{
    QMatrix4x4 mat;
    mat.setRow(0, QVector4D(GLMmat[0][0],GLMmat[0][1],GLMmat[0][2],GLMmat[0][3]));
    mat.setRow(1, QVector4D(GLMmat[1][0],GLMmat[1][1],GLMmat[1][2],GLMmat[1][3]));
    mat.setRow(2, QVector4D(GLMmat[2][0],GLMmat[2][1],GLMmat[2][2],GLMmat[2][3]));
    mat.setRow(3, QVector4D(GLMmat[3][0],GLMmat[3][1],GLMmat[3][2],GLMmat[3][3]));
    return mat;
}

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));

    drawTimer = new QTimer(this);
    connect(drawTimer,SIGNAL(timeout()),this,SLOT(frame()));
    drawTimer->start(17);

    setMouseTracking(true);
    camera = new Camera();
    interaction = new Interaction();
    CalculateProjection(width()/height(),60.0f,0.1f,10000.0f);
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
    CalculateProjection(w/h,45,0.1f,10000.0f);
}
QImage OpenGLWidget::getScreenshot()
{
    makeCurrent();
    return grabFramebuffer();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
      event->ignore();
    }
    else
    {
      Input::registerKeyPress(event->key());
    }

}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
      event->ignore();
    }
    else
    {
      Input::registerKeyRelease(event->key());
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    Input::registerMousePress(event->button());
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Input::registerMouseRelease(event->button());
}

void OpenGLWidget::enterEvent(QEvent *)
{
    grabKeyboard();
}

void OpenGLWidget::leaveEvent(QEvent *)
{
    releaseKeyboard();
}

void OpenGLWidget::finalizeGL()
{
    std::cout << "finalizeGL()"<< std::endl;
    ResourceManager::Instance()->ClearResources();
}

void OpenGLWidget::frame()
{
    interaction->update();

    update();

    Input::update();
}

void OpenGLWidget::DrawScene()
{

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
            ShaderSetUp(shader, trans, mr);
            //draw the model
            mr->GetModel()->DrawMeshes();

            shader->shaderProgram.release();
        }
    }
}

void OpenGLWidget::CalculateProjection(float aspect, float fovy, float nearPlane, float farPlane)
{
    projection.setToIdentity();
    projection.perspective(qDegreesToRadians(fovy),aspect,nearPlane,farPlane);
}

void OpenGLWidget::ShaderSetUp(ShaderProgram* shader, Transform* trans, ModelRender* mr)
{
    QMatrix4x4 viewMat = GLMToQt(camera->GetViewMatrix());

    if(shader->name == "test")
    {
        shader->shaderProgram.setUniformValue("projectionMatrix", projection);
        QMatrix4x4 worldView;
        worldView.setToIdentity();
        worldView *= viewMat * MatGeoLibToQt(trans->GetOpenGLTransformMatrix());
        shader->shaderProgram.setUniformValue("worldViewMatrix",worldView);
    }

    if(shader->name == "model")
    {
        shader->shaderProgram.setUniformValue("model", MatGeoLibToQt(trans->GetOpenGLTransformMatrix()));
        shader->shaderProgram.setUniformValue("view", viewMat);
        shader->shaderProgram.setUniformValue("projection",projection);
    }
}
