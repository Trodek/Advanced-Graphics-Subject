#ifndef MESH_H
#define MESH_H

#define VERTEX_ATTRIBUTE_NUM 16

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int ncomp = 0;
};

class VertexFormat
{
public:
    void SetVertexAttribute(int location, int offset, int ncomp)
    {
        attribute[location].enabled = true;
        attribute[location].offset = offset;
        attribute[location].ncomp = ncomp;
        size += ncomp*sizeof(float);
    }

    VertexAttribute attribute[VERTEX_ATTRIBUTE_NUM];
    int size = 0;
};

class Mesh
{
public:
    Mesh(VertexFormat vertFormat, void *data, int size);
    Mesh(VertexFormat vertFormat, void *data, int size, unsigned int* indices, int indices_count);
    ~Mesh();

    void update();
    void draw();
    void destroy();

private:
    unsigned char *data = nullptr;
    size_t data_size = 0;

    unsigned int* indices = nullptr;
    size_t indices_size = 0;

    VertexFormat vertexFormat;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLVertexArrayObject vao;

};

#endif // MESH_H
