#include "input.h"
#include <iostream>

Input* Input::instance = nullptr;

Input *Input::Instance()
{
    if(instance == nullptr)
    {
        instance = new Input();
    }

    return instance;
}

Input::Input()
{
    for(int i = 0; i < MAX_KEYS; ++i)
    {
        keys[i] = KeyState::Idle;
    }
    for(int i = 0; i < MAX_BUTTONS; ++i)
    {
        mouseButton[i] = MouseButtonState::Idle;
    }
}

void Input::keyPressEvent(QKeyEvent *event)
{
    if(event != nullptr)
        keys[event->key()] = KeyState::Down;
}

void Input::keyReleaseEvent(QKeyEvent *event)
{
    if(event != nullptr)
        keys[event->key()] = KeyState::Up;
}

void Input::mousePressEvent(QMouseEvent *event)
{
    if(event != nullptr)
        mouseButton[event->button()] = MouseButtonState::Down;
}

void Input::mouseMoveEvent(QMouseEvent *event)
{
    mouse_x_prev = mouse_x;
    mouse_y_prev = mouse_y;

    if(event != nullptr)
    {
        mouse_x = event->x();
        mouse_y = event->y();
    }
}

void Input::mouseReleaseEvent(QMouseEvent *event)
{
    if(event != nullptr)
        mouseButton[event->button()] = MouseButtonState::Up;
}

void Input::UpdateStates()
{
    for(int i = 0; i < MAX_KEYS; ++i)
    {
        if(keys[i] == KeyState::Down)
            keys[i] = KeyState::Pressed;
        if(keys[i] == KeyState::Up)
            keys[i] = KeyState::Idle;
    }
    for(int i = 0; i < MAX_BUTTONS; ++i)
    {
        if(mouseButton[i] == MouseButtonState::Down)
            mouseButton[i] = MouseButtonState::Pressed;
        if(mouseButton[i] == MouseButtonState::Up)
            mouseButton[i] = MouseButtonState::Idle;
    }
}
