#ifndef MATERIAL_H
#define MATERIAL_H

#include "resourcemanager.h"
#include "texture.h"

class Material : public Resource
{
public:
    Material();

    void update();
    void destroy();

public:

    class Texture* albedo = nullptr;
    class Texture* normal = nullptr;
    class Texture* specular = nullptr;
    class Texture* height = nullptr;
};

#endif // MATERIAL_H
