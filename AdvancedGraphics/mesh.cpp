#include "render.h"
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
            Render::Instance()->GetFuncs().glEnableVertexAttribArray(GLuint(loc));
            Render::Instance()->GetFuncs().glVertexAttribPointer(GLuint(loc), attr.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*)attr.offset);

        }
    }

    //Release
    vao.release();
    vbo.release();
    if(ibo.isCreated())
        ibo.release();
}

void Mesh::draw()
{
    int num_vert = data_size/vertexFormat.size;
    vao.bind();
    if(indices_size > 0)
    {
        Render::Instance()->GetFuncs().glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        Render::Instance()->GetFuncs().glDrawArrays(GL_TRIANGLES, 0, num_vert);
    }
    vao.release();
}

void Mesh::destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(ibo.isCreated()) ibo.destroy();
    if(vao.isCreated()) vao.destroy();
}
