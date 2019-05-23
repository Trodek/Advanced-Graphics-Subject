#include "transform.h"

Transform::Transform() : Component(Component::Type::Transform)
{
    position = QVector3D(0,0,0);
    scale = QVector3D(1,1,1);
    rotation = QQuaternion();

    trans_mat.setToIdentity();
}

QQuaternion Transform::GetRotation() const
{
    return rotation;
}

QVector3D Transform::GetEulerRotation() const
{
    return rotation.toEulerAngles();
}

QMatrix4x4 Transform::GetTransformMatrix()
{
    if(dirty)
    {
        trans_mat.setToIdentity();
        trans_mat.translate(position);
        trans_mat.rotate(rotation);
        trans_mat.scale(scale);
    }

    return trans_mat;
}

void Transform::SetRotation(QQuaternion rot)
{
    rotation = rot;
    dirty = true;
}

void Transform::SetEulerRotation(QVector3D rot)
{
    rotation.fromEulerAngles(rot);
    dirty = true;
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
    dirty = true;
}

void Transform::SetScale(QVector3D scale)
{
    this->scale = scale;
    dirty = true;
}
