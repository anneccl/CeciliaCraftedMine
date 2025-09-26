#include "chunk.h"

Chunk::Chunk() : m_blocks(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z)
{
}

void Chunk::RemoveBlock(int x, int y, int z)
{
    SetBlock(x, y, z, BTYPE_AIR);
}

void Chunk::SetBlock(int x, int y, int z, BlockType type)
{
    m_blocks.Set(x, y, z, type);
}

BlockType Chunk::GetBlock(int x, int y, int z) const
{
    return m_blocks.Get(x, y, z);
}