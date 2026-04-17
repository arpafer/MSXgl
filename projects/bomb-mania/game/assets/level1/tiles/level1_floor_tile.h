#pragma once

#include "msxgl.h"
#include "color.h"

#define LEVEL1_FLOOR_TILE_COUNT 4
#define LEVEL1_FLOOR_TILE_SIZE 8

#define LEVEL1_TILE_FLOOR_TL 0
#define LEVEL1_TILE_FLOOR_TR 1
#define LEVEL1_TILE_FLOOR_BL 2
#define LEVEL1_TILE_FLOOR_BR 3

// SCREEN 2 floor tiles inspired by the Bomb-Mania C64 arena background.
// Each logical floor block is now 2x2 tiles.
static const u8 g_Level1FloorTilePatterns[LEVEL1_FLOOR_TILE_COUNT * LEVEL1_FLOOR_TILE_SIZE] =
{
    // =========================================================
    // FLOOR 2x2
    // pale ground with sparse green grass marks
    // =========================================================

    // TL
    0x00,
    0x08,
    0x14,
    0x00,
    0x40,
    0x20,
    0x00,
    0x00,

    // TR
    0x00,
    0x10,
    0x28,
    0x00,
    0x02,
    0x04,
    0x00,
    0x00,

    // BL
    0x00,
    0x00,
    0x01,
    0x02,
    0x00,
    0x14,
    0x08,
    0x00,

    // BR
    0x00,
    0x00,
    0x80,
    0x40,
    0x00,
    0x28,
    0x10,
    0x00,
};

static const u8 g_Level1FloorTileColors[LEVEL1_FLOOR_TILE_COUNT * LEVEL1_FLOOR_TILE_SIZE] =
{
    // =========================================================
    // FLOOR 2x2 COLORS
    // foreground = light green / gray details
    // background = white / pale ground
    // =========================================================

    // TL
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),

    // TR
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),

    // BL
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),

    // BR
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
};