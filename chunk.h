#ifndef CHUNK_H
#define CHUNK_H

#include "array3d.h"

class Chunk 
{
public:
    Chunk();

    void RemoveBlock(int x, int y, int z);
    void SetBlock(int x, int y, int z, BlockType type);
    BlockType GetBlock(int x, int y, int z) const;

    private: 
    Array3d<BlockType> m_blocks;
    Mesh m_Mesh;
};

#endif /* CHUNK_H */
