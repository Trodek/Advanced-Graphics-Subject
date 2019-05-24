#ifndef RENDER_H
#define RENDER_H

#include <QOpenGLFunctions_3_3_Core>

class Render
{
public:
    static Render *Instance();
    Render();

    QOpenGLFunctions_3_3_Core GetFuncs() const;
    void InitializeGL();

private:
    static Render* instance;

    QOpenGLFunctions_3_3_Core glFuncs;
};

#endif // RENDER_H
