#include "mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
    if (IsValid())
    {
        rl::UnloadModel(m_model);
    }
}

bool Mesh::IsValid() const
{
    return m_isValid;
}

void Mesh::SetMeshData(VertexData *vd, int vertexCount)
{
    assert(vertexCount % 3 == 0); // all triangles

    m_mesh = rl::Mesh();
    m_mesh.vertexCount = vertexCount;
    m_mesh.triangleCount = vertexCount / 3;
    m_mesh.vertices = (float *)rl::MemAlloc(m_mesh.vertexCount * 3 * sizeof(float));
    m_mesh.texcoords = (float *)rl::MemAlloc(m_mesh.vertexCount * 2 * sizeof(float));
    m_mesh.normals = (float *)rl::MemAlloc(m_mesh.vertexCount * 3 * sizeof(float));
    m_mesh.colors = (unsigned char *)rl::MemAlloc(m_mesh.vertexCount * 4 * sizeof(unsigned char));

    int verticesCount = 0;
    int normalsCount = 0;
    int texcoordsCount = 0;
    int colorsCount = 0;

    for (int i = 0; i < vertexCount; ++i)
    {
        VertexData &v = vd[i];

        m_mesh.vertices[verticesCount++] = v.x;
        m_mesh.vertices[verticesCount++] = v.y;
        m_mesh.vertices[verticesCount++] = v.z;

        m_mesh.normals[normalsCount++] = v.nx;
        m_mesh.normals[normalsCount++] = v.ny;
        m_mesh.normals[normalsCount++] = v.nz;

        m_mesh.texcoords[texcoordsCount++] = v.u;
        m_mesh.texcoords[texcoordsCount++] = v.v;

        m_mesh.colors[colorsCount++] = (unsigned char)(v.r * 255);
        m_mesh.colors[colorsCount++] = (unsigned char)(v.g * 255);
        m_mesh.colors[colorsCount++] = (unsigned char)(v.b * 255);
        m_mesh.colors[colorsCount++] = 255;
    }
    rl::UploadMesh(&m_mesh, false);
    m_model = rl::LoadModelFromMesh(m_mesh);

    m_isValid = true;
}

void Mesh::Render(const Texture &texture, const Shader &shader, const Transformation &transformation)
{
    m_model.materials[0].maps[rl::MATERIAL_MAP_DIFFUSE].texture = texture;
    m_model.materials[0].shader = shader;

    const float *v = transformation.GetMatrix().GetInternalValues();
    // m_model.transform = {v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12], v[13], v[14], v[15]};
    m_model.transform = {v[0], v[4], v[8], v[12], v[1], v[5], v[9], v[13], v[2], v[6], v[10], v[14], v[3], v[7], v[11], v[15]};

    rl::DrawModel(m_model, {0, 0, 0}, 1.f, rl::WHITE);
}

int Mesh::Count() const
{
    return m_vertexCount;
}