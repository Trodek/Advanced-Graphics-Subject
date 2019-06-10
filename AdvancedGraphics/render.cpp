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
    glFuncs = new QOpenGLFunctions_3_3_Core();
}

QOpenGLFunctions_3_3_Core* Render::GetFuncs() const
{
    return glFuncs;
}

void Render::InitializeGL()
{

}

void Render::DrawScene()
{
    AppManager::Instance()->GetOpenGLWidget()->MakeCurrent();

}
