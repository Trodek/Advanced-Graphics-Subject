#ifndef TEXTURE_H
#define TEXTURE_H

#include "resourcemanager.h"

class Texture : public Resource
{
public:
    Texture();

    void update(){}
    void destroy(){}

    void loadFromFile(QString path);

public:
    uint id;
};

#endif // TEXTURE_H
