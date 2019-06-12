#include "Transform.h"
#include "MathGeoLib.h"
#include "Math/float3.h"
#include "Math/Quat.h"

Transform::Transform() : Component(Component::Type::Transform)
{
    ResetTransform();
}

Transform::~Transform()
{
}

float3 Transform::GetPosition() const
{
    return position;
}

float3 Transform::GetEulerRotation() const
{
    float3 deg_rot = rotation.ToEulerXYZ() * RADTODEG;
    return deg_rot;
}

Quat Transform::GetQuatRotation() const
{
    return rotation;
}

float3 Transform::GetScale() const
{
    return scale;
}

float4x4 Transform::GetOpenGLTransformMatrix()
{
    if(update_trans)
    {
        update_trans = false;
        CalculateTransformMatrix();
    }

    return trans.Transposed();
}

float4x4 Transform::GetTransformMatrix()
{
    if(update_trans)
    {
        update_trans = false;
        CalculateTransformMatrix();
    }

    return trans;
}

void Transform::SetPosition(float3 pos)
{
    position = pos;
    update_trans = true;
}

void Transform::SetEulerRotation(float3 rot)
{
    rotation = Quat::FromEulerXYZ(DEGTORAD*rot.x, DEGTORAD*rot.y, DEGTORAD*rot.z);
    update_trans = true;
}

void Transform::SetQuatRotation(Quat quat)
{
    rotation = quat;
    update_trans = true;
}

void Transform::SetScale(float3 size)
{
    scale = size;
    update_trans = true;
}

void Transform::Translate(float3 translation)
{
    position += translation;
    update_trans = true;
}

// Rotates the object the specidied amout of euler angles
// ex: x_rot = curr_rot + rot.x
void Transform::RotateEuler(float3 rot)
{
    float3 curr = rotation.ToEulerXYZ();
    curr += (rot * DEGTORAD);
    rotation.FromEulerXYZ(curr.x, curr.y, curr.z);
    update_trans = true;
}

void Transform::RotateQuat(Quat rot)
{
    rot.Mul(rotation);
    rotation = rot;
    update_trans = true;
}

void Transform::ResetTransform()
{
    position = float3::zero;
    rotation = Quat::identity;
    scale.Set(1.f,1.f,1.f);
}

void Transform::CalculateTransformMatrix()
{
    trans = float4x4::FromTRS(position, rotation, scale);
    update_trans = false;
}

void Transform::Save(QJsonObject &file) const
{
    file["type"] = GetType();
    file["pos_x"] = position.x;
    file["pos_y"] = position.y;
    file["pos_z"] = position.z;

    file["rot_x"] = rotation.ToEulerXYZ().x;
    file["rot_y"] = rotation.ToEulerXYZ().y;
    file["rot_z"] = rotation.ToEulerXYZ().z;

    file["scale_x"] = scale.x;
    file["scale_y"] = scale.y;
    file["scale_z"] = scale.z;
}

void Transform::Load(const QJsonObject &file)
{
    float3 pos(file["pos_x"].toDouble(),file["pos_y"].toDouble(),file["pos_z"].toDouble());
    float3 rot(file["rot_x"].toDouble(),file["rot_y"].toDouble(),file["rot_z"].toDouble());
    float3 scale(file["scale_x"].toDouble(),file["scale_y"].toDouble(),file["scale_z"].toDouble());

    SetPosition(pos);
    SetEulerRotation(rot);
    SetScale(scale);
    update_trans = true;
}
