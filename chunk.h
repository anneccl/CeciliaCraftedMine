#ifndef CHUNK_H
#define CHUNK_H

#include "array3d.h"
#include "mesh.h"

class Chunk 
{
public:
    Chunk();

    void RemoveBlock(int x, int y, int z);
    void SetBlock(int x, int y, int z, BlockType type);
    BlockType GetBlock(int x, int y, int z) const;
    void Update();
    void Render(const Texture &texture, const Shader &shader, const Transformation &transformation);
    bool IsDirty() const;

    private: 
    Array3d<BlockType> m_blocks;
    Mesh m_Mesh;
    bool m_isDirty = true; //Indique si il y a un changement dans chunk 

    void AddBlockToMesh(Mesh::VertexData *vd, int &count, BlockType bt, int x, int y, int z);
};

#endif /* CHUNK_H */
