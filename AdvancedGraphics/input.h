#ifndef INPUT_H
#define INPUT_H

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>

enum class KeyState { Idle, Up, Pressed, Down };

enum class MouseButtonState{ Idle,Up,Pressed,Down};

#define MAX_BUTTONS 10
#define MAX_KEYS 600

class Input
{
public:
    static Input *Instance();
    Input();

    //Process events
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void UpdateStates();

    KeyState keys[MAX_KEYS];
    MouseButtonState mouseButton[MAX_BUTTONS];

    int mouse_x = 0;
    int mouse_y = 0;
    int mouse_x_prev = 0;
    int mouse_y_prev = 0;

private:
    static Input* instance;
};

#endif // INPUT_H
