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

void Transform::Save(QJsonObject &file) const
{
    file["type"] = GetType();
    file["pos_x"] = position.x();
    file["pos_y"] = position.y();
    file["pos_z"] = position.z();

    file["rot_x"] = rotation.toEulerAngles().x();
    file["rot_y"] = rotation.toEulerAngles().y();
    file["rot_z"] = rotation.toEulerAngles().z();

    file["scale_x"] = scale.x();
    file["scale_y"] = scale.y();
    file["scale_z"] = scale.z();
}

void Transform::Load(const QJsonObject &file)
{
    QVector3D pos(file["pos_x"].toDouble(),file["pos_y"].toDouble(),file["pos_z"].toDouble());
    QVector3D rot(file["rot_x"].toDouble(),file["rot_y"].toDouble(),file["rot_z"].toDouble());
    QVector3D scale(file["scale_x"].toDouble(),file["scale_y"].toDouble(),file["scale_z"].toDouble());

    SetPosition(pos);
    SetEulerRotation(rot);
    SetScale(scale);
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
