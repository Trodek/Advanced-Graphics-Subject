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
    if(Input::Instance()->mouseButton[Qt::RightButton] == MouseButtonState::Pressed)
    {
        state = State::Navigate;
    }
    return false;
}

bool Interaction::navigate()
{
    bool ret = false;

    if(Input::Instance()->mouseButton[Qt::RightButton] == MouseButtonState::Idle)
    {
        state = State::Idle;
    }
    else if(Input::Instance()->keys[Qt::Key_O] == KeyState::Down)
    {
        state = State::Orbit;
    }
    else
    {
        QVector3D translation;
        if(Input::Instance()->keys[Qt::Key_W] == KeyState::Pressed)
        {
            translation += AppManager::Instance()->GetOpenGLWidget()->camera->forward();
            ret = true;
        }
        if(Input::Instance()->keys[Qt::Key_A] == KeyState::Pressed)
        {
            translation -= AppManager::Instance()->GetOpenGLWidget()->camera->right();
            ret = true;
        }
        if(Input::Instance()->keys[Qt::Key_S] == KeyState::Pressed)
        {
            translation -= AppManager::Instance()->GetOpenGLWidget()->camera->forward();
            ret = true;
        }
        if(Input::Instance()->keys[Qt::Key_D] == KeyState::Pressed)
        {
            translation += AppManager::Instance()->GetOpenGLWidget()->camera->right();
            ret = true;
        }
        if(Input::Instance()->keys[Qt::Key_Q] == KeyState::Pressed)
        {
            translation += AppManager::Instance()->GetOpenGLWidget()->camera->up();
            ret = true;
        }
        if(Input::Instance()->keys[Qt::Key_E] == KeyState::Pressed)
        {
            translation -= AppManager::Instance()->GetOpenGLWidget()->camera->up();
            ret = true;
        }
        if(Input::Instance()->mouse_x_prev != Input::Instance()->mouse_x || Input::Instance()->mouse_y_prev != Input::Instance()->mouse_y)
        {
            int offset_x = Input::Instance()->mouse_x - Input::Instance()->mouse_x_prev;
            int offset_y = Input::Instance()->mouse_y - Input::Instance()->mouse_y_prev;
            AppManager::Instance()->GetOpenGLWidget()->camera->rotate(-rotSpeed*offset_x,Camera3D::LocalUp);
            AppManager::Instance()->GetOpenGLWidget()->camera->rotate(-rotSpeed*offset_x,AppManager::Instance()->GetOpenGLWidget()->camera->right());
            ret = true;
        }
        AppManager::Instance()->GetOpenGLWidget()->camera->translate(moveSpeed*translation);

    }
    return ret;
}

bool Interaction::orbit()
{
    // TODO
    return false;
}
