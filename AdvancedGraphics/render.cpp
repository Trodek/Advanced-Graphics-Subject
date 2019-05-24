#include "render.h"

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
