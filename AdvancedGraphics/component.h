#ifndef COMPONENT_H
#define COMPONENT_H

#include <QJsonObject>

class Component
{
public:
    enum Type
    {
        Null,
        Light,
        ModelRenderer,
        Transform,      
    };

public:
    Component(Type type);

    Type GetType()const;

    virtual void Save(QJsonObject& file) const = 0;
    virtual void Load(const QJsonObject& file) = 0;

private:
    Type type = Type::Null;
};

#endif // COMPONENT_H
