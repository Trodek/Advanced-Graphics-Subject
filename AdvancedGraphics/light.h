#ifndef LIGHT_H
#define LIGHT_H

#include <QColor>

#include "component.h"

class Light : public Component
{
public:

    enum Type{
        Directional,
        Point,
    };

    Light();

    void UpdateUI();

    void Save(QJsonObject &file) const;
    void Load(const QJsonObject &file);

public:
    QColor color;
    Type type = Directional;
    float intensity = 1.0f;

};

#endif // LIGHT_H
