#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Transform : public Component
{
public:
    Transform();

    QVector3D GetPosition() const;
    QVector3D GetScale() const;
    QQuaternion GetRotation() const;
    QVector3D GetEulerRotation() const;
    QMatrix4x4 GetTransformMatrix();

    void SetPosition(QVector3D pos);
    void SetScale(QVector3D scale);
    void SetRotation(QQuaternion rot);
    void SetEulerRotation(QVector3D rot);

    void Save(QJsonObject& file) const;
    void Load(const QJsonObject& file);

private:

   QVector3D position;
   QVector3D scale;
   QQuaternion rotation;
   QMatrix4x4 trans_mat;

   bool dirty = false;
};

#endif // TRANSFORM_H
