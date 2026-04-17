#pragma once

#include "msxgl.h"

#define LEVEL1_LOGIC_COLS 16
#define LEVEL1_LOGIC_ROWS 10
#define LEVEL1_LOGIC_SIZE (LEVEL1_LOGIC_COLS * LEVEL1_LOGIC_ROWS)

#define LEVEL1_BLOCK_FLOOR          0
#define LEVEL1_BLOCK_INDESTRUCTIBLE 1
#define LEVEL1_BLOCK_DESTRUCTIBLE   2

static const u8 g_Level1LogicMap[LEVEL1_LOGIC_SIZE] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,2,2,2,2,2,2,2,2,0,0,0,1,
    1,0,1,0,2,1,0,1,0,1,0,1,0,1,0,1,
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
    1,2,1,2,1,0,1,0,1,0,1,0,1,2,2,1,
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
    1,2,1,0,1,0,1,0,1,0,1,0,1,2,0,1,
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,0,1,
    1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
