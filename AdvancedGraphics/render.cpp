#include "render.h"
#include "scene.h"
#include "modelrender.h"
#include "model.h"
#include "shaderprogram.h"
#include "gameobject.h"
#include <vector>
#include "transform.h"
#include <QtMath>
#include "appmanager.h"

Render* Render::instance = nullptr;

Render *Render::Instance()
{
    if(instance == nullptr)
    {
        instance = new Render();
    }

    return instance;
}

Render::Render()
{
    InitializeGL();
}

QOpenGLFunctions_3_3_Core Render::GetFuncs() const
{
    return glFuncs;
}

void Render::InitializeGL()
{
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setMinorVersion(3);
    format.setMajorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(0);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);
}

void Render::DrawScene()
{
    AppManager::Instance()->GetOpenGLWidget()->MakeCurrent();
    std::vector<GameObject*> objects = Scene::Instance()->GetObjectsToDraw();

    for(GameObject* go : objects)
    {
        //get the needed components to render the object
        Transform* trans = (Transform*)go->GetComponentByType(Component::Type::Transform);
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);

        //bind the shader
        ShaderProgram* shader = mr->GetShaderProgram();

        if(shader == nullptr || mr->GetModel() == nullptr) continue;

        shader->shaderProgram.bind();

        ///common properties
        shader->shaderProgram.setUniformValue("projectionMatirx",projection);
        shader->shaderProgram.setUniformValue("worldViewMatrix",trans->GetTransformMatrix()); //mult by view when camera done

        //draw the model
        mr->GetModel()->DrawMeshes();

        shader->shaderProgram.release();
    }
}

void Render::CalculateProjection(float aspect, float fovy, float nearPlane, float farPlane)
{
    projection.setToIdentity();

    float f = 1/qTan(fovy/2);

    QVector4D row0 = {f/qDegreesToRadians(aspect),0,0,0};
    QVector4D row1 = {0,f,0,0};
    QVector4D row2 = {0,0,(farPlane+nearPlane)/(nearPlane-farPlane),(2*nearPlane*farPlane)/(nearPlane-farPlane)};
    QVector4D row3 = {0,0,-1,0};

    projection.setRow(0,row0);
    projection.setRow(1,row1);
    projection.setRow(2,row2);
    projection.setRow(3,row3);

}
