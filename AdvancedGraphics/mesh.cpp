#include "render.h"
#include "mesh.h"
#include "appmanager.h"
#include <QOpenGLFunctions>

Mesh::Mesh(VertexFormat vertFormat, void *data, int size) : vertexFormat(vertFormat), data_size(size)
{
    this->data = new unsigned char[size];
    memcpy(this->data, data, size);
    vertexFormat = vertFormat;
    update();
}

Mesh::Mesh(VertexFormat vertFormat, void *data, int size, unsigned int *indices, int indices_count):
    data_size(size), ibo(QOpenGLBuffer::Type::IndexBuffer)
{
    this->data = new unsigned char[size];
    memcpy(this->data, data, size);
    this->indices = new unsigned int[indices_count];
    memcpy(this->indices, indices, indices_count*sizeof(unsigned int));
    vertexFormat = vertFormat;
    this->indices_count = indices_count;
    update();
}

void Mesh::update()
{
    AppManager::Instance()->GetOpenGLWidget()->MakeCurrent();
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
        ibo.allocate(indices, int(indices_count * sizeof(unsigned int)));
        delete[] indices;
        indices = nullptr;
    }

    for(int loc = 0; loc < VERTEX_ATTRIBUTE_NUM; ++loc)
    {
        VertexAttribute attr = vertexFormat.attribute[loc];

        if(attr.enabled)
        {
            AppManager::Instance()->GetOpenGLWidget()->glEnableVertexAttribArray(GLuint(loc));
            AppManager::Instance()->GetOpenGLWidget()->glVertexAttribPointer(GLuint(loc), attr.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*)attr.offset);

        }
    }

    //Release 
    if(ibo.isCreated())
        ibo.release();
    vbo.release();
    vao.release();
}

void Mesh::draw()
{
    int num_vert = data_size/vertexFormat.size;
    vao.bind();
    if(indices_count > 0)
    {
        AppManager::Instance()->GetOpenGLWidget()->glDrawElements(GL_TRIANGLES, int(indices_count), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        AppManager::Instance()->GetOpenGLWidget()->glDrawArrays(GL_TRIANGLES, 0, num_vert);
    }
    vao.release();
}

void Mesh::destroy()
{
    if(vbo.isCreated()) vbo.destroy();
    if(ibo.isCreated()) ibo.destroy();
    if(vao.isCreated()) vao.destroy();
}
