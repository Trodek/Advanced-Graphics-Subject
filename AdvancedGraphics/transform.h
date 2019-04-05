#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>
#include <QQuaternion>

class Transform : public Component
{
public:
    Transform();

    QVector3D GetPosition() const;
    QVector3D GetScale() const;
    QQuaternion GetRotation() const;
    QVector3D GetEulerRotation() const;

    void SetPosition(QVector3D pos);
    void SetScale(QVector3D scale);
    void SetRotation(QQuaternion rot);
    void SetEulerRotation(QVector3D rot);

private:

   QVector3D position;
   QVector3D scale;
   QQuaternion rotation;
};

#endif // TRANSFORM_H
