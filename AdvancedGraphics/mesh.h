#ifndef MESH_H
#define MESH_H

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
        size+=ncomp*sizeof(float);
    }

    VertexAttribute attribute[16]; //Ask Jesus
    int size = 0;
};

class Mesh
{
public:
    Mesh(VertexFormat vertFormat, void *data, int size);
    Mesh(VertexFormat vertFormat, void *data, int size, unsigned int* indices, int indices_count);
    ~Mesh();


private:
    unsigned char *data = nullptr;
    size_t data_size = 0;

    unsigned int* indices = nullptr;

};

#endif // MESH_H
