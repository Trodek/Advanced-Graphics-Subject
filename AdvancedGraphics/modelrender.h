#ifndef MODELRENDER_H
#define MODELRENDER_H

#include "component.h"
#include <QOpenGLShaderProgram>

class Model;
class ShaderProgram;

class ModelRender : public Component
{
public:
    ModelRender();
    virtual ~ModelRender();

    void SetModel(Model* model);
    Model* GetModel();

    void SetShader(ShaderProgram* shader);
    ShaderProgram* GetShaderProgram();

    void Save(QJsonObject& file) const;
    void Load(const QJsonObject& file);

private:
    Model* model = nullptr;
    ShaderProgram* shader = nullptr;
};

#endif // MODELRENDER_H
