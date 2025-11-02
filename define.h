#ifndef DEFINE_H__
#define DEFINE_H__

#include <cmath>
#include <cstdarg>
#include <cstdint>

namespace rl
{
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
} // namespace rl

typedef uint8_t BlockType;
enum BLOCK_TYPE
{
    BTYPE_AIR,
    BTYPE_DIRT,
    BTYPE_GRASS
};

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 128
#define CHUNK_SIZE_Z 16
#define VIEW_DISTANCE 64

#endif