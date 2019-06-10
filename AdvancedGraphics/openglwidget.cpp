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

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));

    drawTimer = new QTimer(this);
    connect(drawTimer,SIGNAL(timeout()),this,SLOT(frame()));
    drawTimer->start(17);

    setMouseTracking(true);
    camera = new Camera3D();
    interaction = new Interaction();
    CalculateProjection(width()/height(),45,0.1f,10000.0f);
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
    Input::Instance()->keyPressEvent(event);
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    Input::Instance()->keyReleaseEvent(event);
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    Input::Instance()->mousePressEvent(event);
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    Input::Instance()->mouseMoveEvent(event);
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Input::Instance()->mouseReleaseEvent(event);
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

    Input::Instance()->UpdateStates();
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
    projection.perspective(fovy,aspect,nearPlane,farPlane);
}

void OpenGLWidget::ShaderSetUp(ShaderProgram* shader, Transform* trans, ModelRender* mr)
{
    if(shader->name == "test")
    {
        shader->shaderProgram.setUniformValue("projectionMatrix", projection);
        QMatrix4x4 worldView;
        worldView.setToIdentity();
        worldView *= camera->toMatrix() * trans->toMatrix();
        shader->shaderProgram.setUniformValue("worldViewMatrix",worldView);
    }

    if(shader->name == "model")
    {
        shader->shaderProgram.setUniformValue("model", trans->toMatrix());
        shader->shaderProgram.setUniformValue("view", camera->toMatrix());
        shader->shaderProgram.setUniformValue("projection",projection);
    }
}
