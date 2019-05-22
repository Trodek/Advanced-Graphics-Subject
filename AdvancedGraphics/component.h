#ifndef COMPONENT_H
#define COMPONENT_H


class Component
{
public:
    enum Type
    {
        Transform,
        Null
    };

public:
    Component(Type type);

    Type GetType()const;

private:
    Type type = Type::Null;
};

#endif // COMPONENT_H
