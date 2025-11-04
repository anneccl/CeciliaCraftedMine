#include "chunk.h"

Chunk::Chunk(bool isChunkTest) : m_blocks(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z)
{
    m_blocks.Reset(BTYPE_AIR);

    if (isChunkTest == true)
    {
        for (int x = 0; x < CHUNK_SIZE_X; ++x)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                for (int y = 0; y < 32; ++y)
                {
                    if (x % 2 == 0 && y % 2 == 0 && z % 2 == 0) // Affiche un cube sur 2
                        SetBlock(x, y, z, BTYPE_DIRT);
                }
            }
        }
    }
    else
    {
        for (int x = 0; x < CHUNK_SIZE_X; ++x)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                for (int y = 0; y < 5; ++y)
                {
                    SetBlock(x, y, z, BTYPE_DIRT);
                }
            }
        }
    }
}

void Chunk::RemoveBlock(int x, int y, int z)
{
    SetBlock(x, y, z, BTYPE_AIR);
    m_isDirty = true;
}

void Chunk::SetBlock(int x, int y, int z, BlockType type)
{
    m_blocks.Set(x, y, z, type);
    m_isDirty = true;
}

BlockType Chunk::GetBlock(int x, int y, int z) const
{
    return m_blocks.Get(x, y, z);
}

void Chunk::Update()
{
    // Update mesh
    if (m_isDirty)
    {
        int maxVertexCount = (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z) * (6 * 6);
        Mesh::VertexData *vd = new Mesh::VertexData[maxVertexCount];
        int count = 0;
        for (int x = 0; x < CHUNK_SIZE_X; ++x)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                for (int y = 0; y < CHUNK_SIZE_Y; ++y)
                {
                    BlockType bt = GetBlock(x, y, z);
                    if (bt != BTYPE_AIR)
                    {
                        AddBlockToMesh(vd, count, bt, x, y, z);
                    }
                }
            }
        }
        m_Mesh.SetMeshData(vd, count);
        delete[] vd;
    }
    m_isDirty = false;
}

void Chunk::Render(const Texture &texture, const Shader &shader, const Transformation &transformation)
{
    m_Mesh.Render(texture, shader, transformation);
}

bool Chunk::IsDirty() const
{
    return m_isDirty;
}

void Chunk::AddBlockToMesh(Mesh::VertexData *vd, int &count, BlockType bt, int x, int y, int z)
{
    // front
    vd[count++] = Mesh::VertexData(x + -.5f, y + -.5f, z + .5f, 0, 0, 1, .8f, .8f, .8f, 0, 0);
    vd[count++] = Mesh::VertexData(x + .5f, y + -.5f, z + .5f, 0, 0, 1, .8f, .8f, .8f, 1, 0);
    vd[count++] = Mesh::VertexData(x + -.5f, y + .5f, z + .5f, 0, 0, 1, .8f, .8f, .8f, 0, 1);
    vd[count++] = Mesh::VertexData(x + -.5f, y + .5f, z + .5f, 0, 0, 1, .8f, .8f, .8f, 0, 1);
    vd[count++] = Mesh::VertexData(x + .5f, y + -.5f, z + .5f, 0, 0, 1, .8f, .8f, .8f, 1, 0);
    vd[count++] = Mesh::VertexData(x + .5f, y + .5f, z + .5f, 0, 0, 1, .8f, .8f, .8f, 1, 1);

    // back
    vd[count++] = Mesh::VertexData(x - 0.5f, y - 0.5f, z - 0.5f, 0, 0, -1, .8f, .8f, .8f, 0, 0);
    vd[count++] = Mesh::VertexData(x - 0.5f, y + 0.5f, z - 0.5f, 0, 0, -1, .8f, .8f, .8f, 0, 1);
    vd[count++] = Mesh::VertexData(x + 0.5f, y - 0.5f, z - 0.5f, 0, 0, -1, .8f, .8f, .8f, 1, 0);
    vd[count++] = Mesh::VertexData(x + 0.5f, y - 0.5f, z - 0.5f, 0, 0, -1, .8f, .8f, .8f, 1, 0);
    vd[count++] = Mesh::VertexData(x - 0.5f, y + 0.5f, z - 0.5f, 0, 0, -1, .8f, .8f, .8f, 0, 1);
    vd[count++] = Mesh::VertexData(x + 0.5f, y + 0.5f, z - 0.5f, 0, 0, -1, .8f, .8f, .8f, 1, 1);

    // right
    vd[count++] = Mesh::VertexData(x + 0.5f, y - 0.5f, z + 0.5f, 1, 0, 0, .9f, .9f, .9f, 0, 0);
    vd[count++] = Mesh::VertexData(x + 0.5f, y - 0.5f, z - 0.5f, 1, 0, 0, .9f, .9f, .9f, 1, 0);
    vd[count++] = Mesh::VertexData(x + 0.5f, y + 0.5f, z + 0.5f, 1, 0, 0, .9f, .9f, .9f, 0, 1);
    vd[count++] = Mesh::VertexData(x + 0.5f, y - 0.5f, z - 0.5f, 1, 0, 0, .9f, .9f, .9f, 1, 0);
    vd[count++] = Mesh::VertexData(x + 0.5f, y + 0.5f, z - 0.5f, 1, 0, 0, .9f, .9f, .9f, 1, 1);
    vd[count++] = Mesh::VertexData(x + 0.5f, y + 0.5f, z + 0.5f, 1, 0, 0, .9f, .9f, .9f, 0, 1);

    // left
    vd[count++] = Mesh::VertexData(x - 0.5f, y - 0.5f, z - 0.5f, -1, 0, 0, .9f, .9f, .9f, 0, 0);
    vd[count++] = Mesh::VertexData(x - 0.5f, y - 0.5f, z + 0.5f, -1, 0, 0, .9f, .9f, .9f, 1, 0);
    vd[count++] = Mesh::VertexData(x - 0.5f, y + 0.5f, z - 0.5f, -1, 0, 0, .9f, .9f, .9f, 0, 1);
    vd[count++] = Mesh::VertexData(x - 0.5f, y - 0.5f, z + 0.5f, -1, 0, 0, .9f, .9f, .9f, 1, 0);
    vd[count++] = Mesh::VertexData(x - 0.5f, y + 0.5f, z + 0.5f, -1, 0, 0, .9f, .9f, .9f, 1, 1);
    vd[count++] = Mesh::VertexData(x - 0.5f, y + 0.5f, z - 0.5f, -1, 0, 0, .9f, .9f, .9f, 0, 1);

    // top
    vd[count++] = Mesh::VertexData(x - 0.5f, y + 0.5f, z + 0.5f, 0, 1, 0, 1, 1, 1, 0, 0);
    vd[count++] = Mesh::VertexData(x + 0.5f, y + 0.5f, z + 0.5f, 0, 1, 0, 1, 1, 1, 1, 0);
    vd[count++] = Mesh::VertexData(x - 0.5f, y + 0.5f, z - 0.5f, 0, 1, 0, 1, 1, 1, 0, 1);
    vd[count++] = Mesh::VertexData(x + 0.5f, y + 0.5f, z + 0.5f, 0, 1, 0, 1, 1, 1, 1, 0);
    vd[count++] = Mesh::VertexData(x + 0.5f, y + 0.5f, z - 0.5f, 0, 1, 0, 1, 1, 1, 1, 1);
    vd[count++] = Mesh::VertexData(x - 0.5f, y + 0.5f, z - 0.5f, 0, 1, 0, 1, 1, 1, 0, 1);

    // bottom
    vd[count++] = Mesh::VertexData(x - 0.5f, y - 0.5f, z + 0.5f, 0, -1, 0, 1, 1, 1, 0, 0);
    vd[count++] = Mesh::VertexData(x - 0.5f, y - 0.5f, z - 0.5f, 0, -1, 0, 1, 1, 1, 0, 1);
    vd[count++] = Mesh::VertexData(x + 0.5f, y - 0.5f, z + 0.5f, 0, -1, 0, 1, 1, 1, 1, 0);
    vd[count++] = Mesh::VertexData(x + 0.5f, y - 0.5f, z + 0.5f, 0, -1, 0, 1, 1, 1, 1, 0);
    vd[count++] = Mesh::VertexData(x - 0.5f, y - 0.5f, z - 0.5f, 0, -1, 0, 1, 1, 1, 0, 1);
    vd[count++] = Mesh::VertexData(x + 0.5f, y - 0.5f, z - 0.5f, 0, -1, 0, 1, 1, 1, 1, 1);
}
