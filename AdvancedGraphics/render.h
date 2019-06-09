#ifndef RENDER_H
#define RENDER_H

#include <QOpenGLFunctions_3_3_Core>

#include <QMatrix4x4>

class Render
{
public:
    static Render *Instance();
    Render();

    QOpenGLFunctions_3_3_Core* GetFuncs() const;
    void InitializeGL();

    void DrawScene();

    void CalculateProjection(float aspect, float fovy, float nearPlane, float farPlane);

private:
    static Render* instance;

    QOpenGLFunctions_3_3_Core* glFuncs;
    QMatrix4x4 projection;
};

#endif // RENDER_H
