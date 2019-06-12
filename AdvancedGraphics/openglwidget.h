#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "shaderprogram.h"
#include "model.h"
#include "camera.h"
#include "interaction.h"
#include "MathGeoLib.h"

class Transform;
class ModelRender;

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

    void MakeCurrent();
    void initializeGL() override; 
    void paintGL() override;
    void resizeGL(int w, int h) override;
    QImage getScreenshot();

    //input
   void keyPressEvent(QKeyEvent* event) override;
   void keyReleaseEvent(QKeyEvent* event) override;
   void mousePressEvent(QMouseEvent* event) override;
   void mouseReleaseEvent(QMouseEvent* event) override;
   void enterEvent(QEvent* ) override;
   void leaveEvent(QEvent*) override;

   void generateFrameBuffer(float w, float h);
   void generateGBufferFBO(float w, float h);

signals:

public slots:
    void DrawScene();
    void finalizeGL();
    void frame();

private:
    void InitTriangle();
    void CalculateProjection(float aspect, float fovy, float nearPlane, float farPlane);
    void ShaderSetUp(ShaderProgram* shader, Transform* trans, ModelRender* mr);
    void LightPass();
    void FindGlError();

private:
    QTimer* drawTimer = nullptr;

    ShaderProgram* triProgram;
    Model* triangle;

    QMatrix4x4 projection;

    //FBO
    ShaderProgram* fboToScreen;

    unsigned int colorTexture;
    unsigned int depthTexture;
    unsigned int fbo;

    //Defered
    ShaderProgram* gPass;
    ShaderProgram* lAmbPass;
    ShaderProgram* lDirPass;
    ShaderProgram* lPointPass;
    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gColorSpec, gDepth, gAlbedoSpec;

public:
    Camera* camera;
    Interaction* interaction;

    bool finalRender = true;
    bool normals = false;
    bool positions = false;
    bool albedo = false;

    float ambientMult = 0.1f;


};

#endif // OPENGLWIDGET_H
