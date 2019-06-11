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
#include "texture.h"
#include <QOpenGLFramebufferObject>

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
    mat.setRow(0, QVector4D(GLMmat[0][0],GLMmat[1][0],GLMmat[2][0],GLMmat[3][0]));
    mat.setRow(1, QVector4D(GLMmat[0][1],GLMmat[1][1],GLMmat[2][1],GLMmat[3][1]));
    mat.setRow(2, QVector4D(GLMmat[0][2],GLMmat[1][2],GLMmat[2][2],GLMmat[3][2]));
    mat.setRow(3, QVector4D(GLMmat[0][3],GLMmat[1][3],GLMmat[2][3],GLMmat[3][3]));
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
    CalculateProjection((float)width()/(float)height(),60.0f,0.1f,10000.0f);
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

    fboToScreen = ResourceManager::Instance()->CreateShaderProgram();
    fboToScreen->SetShaders("../Resources/Shaders/fboToScreen.vs","../Resources/Shaders/fboToScreen.fs");

    gPass = ResourceManager::Instance()->CreateShaderProgram();
    gPass->SetShaders("../Resources/Shaders/Gpass.vs", "../Resources/Shaders/Gpass.fs");

    lPass = ResourceManager::Instance()->CreateShaderProgram();
    lPass->SetShaders("../Resources/Shaders/Lpass.vs", "../Resources/Shaders/Lpass.fs");

    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::paintGL()
{
    MakeCurrent();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //geomerty pass
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    ///clear color
    glClearDepth(1.0);
    glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ///draw scene on fbo
    DrawScene();

    ///bind default
    QOpenGLFramebufferObject::bindDefault();

    //Light pass
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    ///do pass


    glDisable(GL_BLEND);

    //Draw scene to quad
    Model* quad = ResourceManager::Instance()->GetModel("Quad");
    if(fboToScreen->shaderProgram.bind())
    {
        fboToScreen->shaderProgram.setUniformValue("colorTex",0);
        glActiveTexture(GL_TEXTURE0);
        if(finalRender)
            glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        else if(normals)
            glBindTexture(GL_TEXTURE_2D, gNormal);
        else if(positions)
            glBindTexture(GL_TEXTURE_2D, gPosition);
        else if(albedo)
            glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
        quad->DrawMeshes(fboToScreen);
    }


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
    CalculateProjection((float)w/(float)h,45.0f,0.1f,10000.0f);
    generateFrameBuffer((float)w, (float)h);
    generateGBufferFBO((float)w, (float)h);
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

void OpenGLWidget::generateFrameBuffer(float w, float h)
{
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w,h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE: // Everything's OK
    break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_UNSUPPORTED"; break;
    default:
    qDebug() << "Framebuffer ERROR: Unknown ERROR";
    }

    QOpenGLFramebufferObject::bindDefault();

}

void OpenGLWidget::generateGBufferFBO(float w, float h)
{
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    // - position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    // - normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    // - color + specular color buffer
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

    // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    glGenTextures(1, &gDepth);
    glBindTexture(GL_TEXTURE_2D, gDepth);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE: // Everything's OK
    break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
    qDebug() << "Framebuffer ERROR: GL_FRAMEBUFFER_UNSUPPORTED"; break;
    default:
    qDebug() << "Framebuffer ERROR: Unknown ERROR";
    }

    QOpenGLFramebufferObject::bindDefault();

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
        //shader = gPass; // hardcode this shader ftm

        if(shader == nullptr || mr->GetModel() == nullptr) continue;

        if(shader->shaderProgram.bind())
        {
            ShaderSetUp(shader, trans, mr);
            //draw the model
            mr->GetModel()->DrawMeshes(shader);

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
        shader->shaderProgram.setUniformValue("model", MatGeoLibToQt(trans->GetTransformMatrix()));
        shader->shaderProgram.setUniformValue("view", viewMat);
        shader->shaderProgram.setUniformValue("projection",projection);
        shader->shaderProgram.setUniformValue("viewPos", QVector3D(camera->Position.x,camera->Position.y,camera->Position.z));
        shader->shaderProgram.setUniformValue("lightPos", QVector3D(50.0,50.0,-50.0));
    }
    if(shader->name == "Gpass")
    {
        shader->shaderProgram.setUniformValue("model", MatGeoLibToQt(trans->GetTransformMatrix()));
        shader->shaderProgram.setUniformValue("view", viewMat);
        shader->shaderProgram.setUniformValue("projection",projection);
    }
}
