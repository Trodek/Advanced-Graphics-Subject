#include "shaderprogram.h"
#include "appmanager.h"
#include "resourcemanager.h"

ShaderProgram::ShaderProgram() : Resource(Resource::Type::Shader)
{

}

void ShaderProgram::update()
{
    AppManager::Instance()->GetOpenGLWidget()->MakeCurrent();
    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, vertPath);
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,fragPath);
    shaderProgram.link();
}

void ShaderProgram::destroy()
{
    shaderProgram.release();
}

void ShaderProgram::SetShaders(QString vertPath, QString fragPath)
{
    this->vertPath = vertPath;
    this->fragPath = fragPath;

    shaderProgram.removeAllShaders();

    this->name = ResourceManager::Instance()->GetNameFrom(vertPath.toStdString()).c_str();
    update();
}
