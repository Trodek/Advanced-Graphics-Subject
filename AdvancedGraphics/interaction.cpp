#include "interaction.h"
#include "input.h"
#include "openglwidget.h"
#include "camera.h"
#include "appmanager.h"

Interaction::Interaction()
{

}

bool Interaction::update()
{
    bool changed = false;

    switch (state) {
    case State::Idle:
        changed = idle();
        break;
    case State::Navigate:
        changed = navigate();
        break;
    case State::Orbit:
        changed = orbit();
        break;
    default:
        break;
    }

    return  changed;
}

bool Interaction::idle()
{
    if(Input::buttonPressed(Qt::RightButton))
    {
        state = State::Navigate;
    }
    return false;
}

bool Interaction::navigate()
{
    bool ret = false;

    if(Input::buttonReleased(Qt::RightButton))
    {
        state = State::Idle;
    }
    else if(Input::keyTriggered(Qt::Key_O))
    {
        state = State::Orbit;
    }
    else
    {
        QVector3D translation;
        if(Input::keyPressed(Qt::Key_W))
        {
            translation += AppManager::Instance()->GetOpenGLWidget()->camera->forward();
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_A))
        {
            translation -= AppManager::Instance()->GetOpenGLWidget()->camera->right();
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_S))
        {
            translation -= AppManager::Instance()->GetOpenGLWidget()->camera->forward();
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_D))
        {
            translation += AppManager::Instance()->GetOpenGLWidget()->camera->right();
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_Q))
        {
            translation += AppManager::Instance()->GetOpenGLWidget()->camera->up();
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_E))
        {
            translation -= AppManager::Instance()->GetOpenGLWidget()->camera->up();
            ret = true;
        }

        AppManager::Instance()->GetOpenGLWidget()->camera->rotate(-rotSpeed*Input::mouseDelta().x(),Camera3D::LocalUp);
        AppManager::Instance()->GetOpenGLWidget()->camera->rotate(-rotSpeed*Input::mouseDelta().y(),AppManager::Instance()->GetOpenGLWidget()->camera->right());

        AppManager::Instance()->GetOpenGLWidget()->camera->translate(moveSpeed*translation);

    }
    return ret;
}

bool Interaction::orbit()
{
    // TODO
    return false;
}
