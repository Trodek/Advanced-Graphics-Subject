#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

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

signals:

public slots:
    void DrawScene();
    void finalizeGL();

private:
    QTimer* drawTimer = nullptr;


};

#endif // OPENGLWIDGET_H
