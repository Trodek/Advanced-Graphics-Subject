#include "transform.h"

Transform::Transform() : Component(Component::Type::Transform)
{
    position = QVector3D(0,0,0);
    scale = QVector3D(1,1,1);
    rotation = QQuaternion();
}

QQuaternion Transform::GetRotation() const
{
    return rotation;
}

QVector3D Transform::GetEulerRotation() const
{
    return rotation.toEulerAngles();
}

void Transform::SetRotation(QQuaternion rot)
{
    rotation = rot;
}

void Transform::SetEulerRotation(QVector3D rot)
{
    rotation.fromEulerAngles(rot);
}

QVector3D Transform::GetPosition() const
{
    return position;
}

QVector3D Transform::GetScale() const
{
    return scale;
}

void Transform::SetPosition(QVector3D pos)
{
    position = pos;
}

void Transform::SetScale(QVector3D scale)
{
    this->scale = scale;
}
