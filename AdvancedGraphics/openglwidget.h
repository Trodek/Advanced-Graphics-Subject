#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include "shaderprogram.h"
#include "model.h"

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();

    void MakeCurrent();
    void initializeGL() override; 
    void resizeGL(int w, int h) override;
    QImage getScreenshot();

signals:

public slots:
    void DrawScene();
    void finalizeGL();
    void paintGL() override;

private:
    void InitTriangle();
     void CalculateProjection(float aspect, float fovy, float nearPlane, float farPlane);

private:
    QTimer* drawTimer = nullptr;

    ShaderProgram* triProgram;
    Model* triangle;

    QMatrix4x4 projection;

};

#endif // OPENGLWIDGET_H
