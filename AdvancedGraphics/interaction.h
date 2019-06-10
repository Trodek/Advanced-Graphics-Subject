#ifndef INTERACTION_H
#define INTERACTION_H


class Interaction
{
public:
    Interaction();

    bool update();

private:

    bool idle();
    bool navigate();
    bool orbit();

    enum State { Idle, Navigate, Orbit };
    State state = State::Idle;

    float moveSpeed = 2.5f * 0.17f;
    float rotSpeed = 0.5f * 0.17f;
};

#endif // INTERACTION_H
