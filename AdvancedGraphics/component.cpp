#include "component.h"

Component::Component(Type type): type(type)
{

}

Component::Type Component::GetType() const
{
    return type;
}
