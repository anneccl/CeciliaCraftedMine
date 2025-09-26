#ifndef BLOCKARRAY3D_H
#define BLOCKARRAY3D_H

#include "define.h"

class BlockArray3d
{
public:
    BlockArray3d(int x, int y, int z);
    ~BlockArray3d();
    BlockArray3d(const BlockArray3d &other);

    void Set(int x, int y, int z, BlockType type);
    BlockType Get(int x, int y, int z) const;

    void Reset(BlockType type);

private:
    int GetIndex(int x, int y, int z) const;

private:
    BlockType *m_blocks;
    int m_x, m_y, m_z;
};

#endif /* BLOCKARRAY3D_H */
