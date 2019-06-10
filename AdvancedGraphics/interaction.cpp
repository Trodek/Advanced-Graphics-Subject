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
        if(Input::keyPressed(Qt::Key_W))
        {
            AppManager::Instance()->GetOpenGLWidget()->camera->ProcessKeyboard(Camera_Movement::FORWARD, 0.17f);
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_A))
        {
            AppManager::Instance()->GetOpenGLWidget()->camera->ProcessKeyboard(Camera_Movement::LEFT, 0.17f);
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_S))
        {
            AppManager::Instance()->GetOpenGLWidget()->camera->ProcessKeyboard(Camera_Movement::BACKWARD, 0.17f);
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_D))
        {
            AppManager::Instance()->GetOpenGLWidget()->camera->ProcessKeyboard(Camera_Movement::RIGHT, 0.17f);
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_Q))
        {
            AppManager::Instance()->GetOpenGLWidget()->camera->ProcessKeyboard(Camera_Movement::UP, 0.17f);
            ret = true;
        }
        if(Input::keyPressed(Qt::Key_E))
        {
            AppManager::Instance()->GetOpenGLWidget()->camera->ProcessKeyboard(Camera_Movement::DOWN, 0.17f);
            ret = true;
        }

        AppManager::Instance()->GetOpenGLWidget()->camera->ProcessMouseMovement(Input::mouseDelta().x(),Input::mouseDelta().y());

    }
    return ret;
}

bool Interaction::orbit()
{
    // TODO
    return false;
}
