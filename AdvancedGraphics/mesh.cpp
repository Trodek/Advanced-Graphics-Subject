
#include "mesh.h"
#include <QOpenGLFunctions>

Mesh::Mesh(VertexFormat vertFormat, void *data, int size) : vertexFormat(vertFormat), data_size(size)
{
    this->data = (unsigned char*)data;
}

Mesh::Mesh(VertexFormat vertFormat, void *data, int size, unsigned int *indices, int indices_count):
    vertexFormat(vertFormat), data_size(size), indices(indices), indices_size(indices_count)
{
    this->data = (unsigned char*)data;
}

void Mesh::update()
{
    // vao
    vao.create();
    vao.bind();

    // vbo
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data,int(data_size));
    delete[] data;
    data = nullptr;

    // ibo
    if(indices != nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indices,int(indices_size * sizeof(unsigned int)));
        delete[] indices;
        indices = nullptr;
    }

    for(int loc = 0; loc < VERTEX_ATTRIBUTE_NUM; ++loc)
    {
        VertexAttribute& attr = vertexFormat.attribute[loc];

        if(attr.enabled)
        {

        }
    }
}

void Mesh::draw()
{

}

void Mesh::destroy()
{

}
