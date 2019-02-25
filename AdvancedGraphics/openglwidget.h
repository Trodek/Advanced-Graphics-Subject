#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget* parent);
    ~OpenGLWidget();

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    QImage getScreenshot();

signals:

public slots:

    void finalizeGL();

};

#endif // OPENGLWIDGET_H
