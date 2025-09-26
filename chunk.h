#ifndef CHUNK_H
#define CHUNK_H

#include "blockarray3d.h"

class Chunk 
{
public:
    Chunk();

    void RemoveBlock(int x, int y, int z);
    void SetBlock(int x, int y, int z, BlockType type);
    BlockType GetBlock(int x, int y, int z) const;

    private: 
    BlockArray3d m_blocks;
};

#endif /* CHUNK_H */
