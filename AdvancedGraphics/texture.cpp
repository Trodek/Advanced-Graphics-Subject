#include "texture.h"
#include "appmanager.h"
#include "openglwidget.h"
#include <iostream>
#include <QFile>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() : Resource(Resource::Type::Texture)
{

}

void Texture::loadFromFile(QString path)
{
    AppManager::Instance()->GetOpenGLWidget()->MakeCurrent();
    this->name = ResourceManager::Instance()->GetNameFrom(path.toStdString()).c_str();
    this->path = ResourceManager::Instance()->GetPathFrom(path.toStdString()).c_str();

    AppManager::Instance()->GetOpenGLWidget()->glGenTextures(1,&id);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.toStdString().c_str(),&width,&height,&nrComponents,0);

    if(data != nullptr)
    {
        GLenum format;
        if(nrComponents == 1)
            format = GL_RED;
        if(nrComponents == 3)
            format = GL_RGB;
        if(nrComponents == 4)
            format = GL_RGBA;

        AppManager::Instance()->GetOpenGLWidget()->glBindTexture(GL_TEXTURE_2D,id);
        AppManager::Instance()->GetOpenGLWidget()->glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        AppManager::Instance()->GetOpenGLWidget()->glGenerateMipmap(GL_TEXTURE_2D);

        AppManager::Instance()->GetOpenGLWidget()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        AppManager::Instance()->GetOpenGLWidget()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        AppManager::Instance()->GetOpenGLWidget()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        AppManager::Instance()->GetOpenGLWidget()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Error loading textur with path: " << path.toStdString() << std::endl;
        stbi_image_free(data);
    }
}
