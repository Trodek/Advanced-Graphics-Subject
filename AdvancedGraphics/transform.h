#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <qvector2d.h>

class Transform : public Component
{
public:
    Transform();

    QVector2D GetPosition() const;
    QVector2D GetScale() const;

    void SetPosition(QVector2D pos);
    void SetScale(QVector2D scale);

private:

   QVector2D position;
   QVector2D scale;
};

#endif // TRANSFORM_H
