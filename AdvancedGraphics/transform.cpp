#include "transform.h"

Transform::Transform() : Component(Component::Type::Transform)
{
    position = QVector2D(0,0);
    scale = QVector2D(1,1);
}

QVector2D Transform::GetPosition() const
{
    return position;
}

QVector2D Transform::GetScale() const
{
    return scale;
}

void Transform::SetPosition(QVector2D pos)
{
    position = pos;
}

void Transform::SetScale(QVector2D scale)
{
    this->scale = scale;
}
