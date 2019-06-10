#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include "Component.h"
#include "MathGeoLib.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class Transform : public Component
{
public:
    Transform();
    ~Transform();

    void Save(QJsonObject &file) const;
    void Load(const QJsonObject &file);

    float3 GetPosition() const;
    float3 GetEulerRotation() const;
    Quat GetQuatRotation() const;
    float3 GetScale() const;
    float4x4 GetOpenGLTransformMatrix() ;
    float4x4 GetTransformMatrix() ;

    void SetPosition(float3 pos);
    void SetEulerRotation(float3 rot);
    void SetQuatRotation(Quat quat);
    void SetScale(float3 size);

    void Translate(float3 translation);
    void RotateEuler(float3 rot);
    void RotateQuat(Quat rot);

    void ResetTransform();

private:

    void CalculateTransformMatrix();

private:
    float3 position;
    Quat rotation;
    float3 scale;

    float4x4 trans;

    bool update_trans = true;
};

#endif // TRANSFORM3D_H
