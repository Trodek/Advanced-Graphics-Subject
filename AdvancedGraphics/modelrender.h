#ifndef MODELRENDER_H
#define MODELRENDER_H

#include "component.h"
#include <QOpenGLShaderProgram>

class Model;
class ShaderProgram;
class Texture;

class ModelRender : public Component
{
public:
    ModelRender();
    virtual ~ModelRender();

    void SetModel(Model* model);
    Model* GetModel();

    void SetShader(ShaderProgram* shader);
    ShaderProgram* GetShaderProgram();

    void SetAlbedo(Texture* tex);
    Texture* GetAlbedo();

    void SetNormal(Texture* tex);
    Texture* GetNormal();

    void Save(QJsonObject& file) const;
    void Load(const QJsonObject& file);

private:
    Model* model = nullptr;
    ShaderProgram* shader = nullptr;

    Texture* albedo = nullptr;
    Texture* normal = nullptr;
};

#endif // MODELRENDER_H
