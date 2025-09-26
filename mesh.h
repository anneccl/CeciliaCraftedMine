#ifndef MESH_H
#define MESH_H

#include "define.h"
#include "texture.h"
#include "shader.h"
#include "transformation.h"
#include <cassert>

class Mesh
{
public:
    struct VertexData
    {
        float x, y, z;    // position
        float nx, ny, nz; // normal
        float r, g, b;    // light
        float u, v;       // tex coord

        VertexData() {}
        VertexData(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float u, float v) : x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), r(r), g(g), b(b), u(u), v(v) {}
    };

public:
    Mesh();
    ~Mesh();
    bool IsValid() const;
    void SetMeshData(VertexData *vd, int vertexCount);
    void Render(const Texture &texture, const Shader &shader, const Transformation &transformation = Transformation());
    int Count() const;

    // Empecher la copie
    Mesh(const Mesh &) = delete;
    Mesh &operator=(const Mesh &) = delete;

private:
    bool m_isValid = false;
    int m_vertexCount = 0;

    rl::Mesh m_mesh;
    rl::Model m_model;
};

#endif /* MESH_H */
