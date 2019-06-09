#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "resourcemanager.h"
#include "QOpenGLShaderProgram"

class ShaderProgram : public Resource
{
public:
    ShaderProgram();

    void update();
    void destroy();

    void SetShaders(QString vertPath, QString fragPath);

    QString vertPath = "";
    QString fragPath = "";
    QOpenGLShaderProgram shaderProgram;

};

#endif // SHADERPROGRAM_H
