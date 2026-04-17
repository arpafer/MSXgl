#pragma once

#include "msxgl.h"
#include "color.h"

#define LEVEL1_WALL_TILE_COUNT 8
#define LEVEL1_WALL_TILE_SIZE 8

#define LEVEL1_TILE_INDESTRUCTIBLE_TL 0
#define LEVEL1_TILE_INDESTRUCTIBLE_TR 1
#define LEVEL1_TILE_INDESTRUCTIBLE_BL 2
#define LEVEL1_TILE_INDESTRUCTIBLE_BR 3

#define LEVEL1_TILE_DESTRUCTIBLE_TL 4
#define LEVEL1_TILE_DESTRUCTIBLE_TR 5
#define LEVEL1_TILE_DESTRUCTIBLE_BL 6
#define LEVEL1_TILE_DESTRUCTIBLE_BR 7

static const u8 g_Level1WallTilePatterns[LEVEL1_WALL_TILE_COUNT * LEVEL1_WALL_TILE_SIZE] =
    {
        // =========================================================
        // INDESTRUCTIBLE BLOCK 2x2
        // yellow block with black border and 4 black dots
        // =========================================================

        // TL
        0xFF,
        0x81,
        0x81,
        0x81,
        0x89,
        0x81,
        0x81,
        0xFF,

        // TR
        0xFF,
        0x81,
        0x81,
        0x81,
        0x91,
        0x81,
        0x81,
        0xFF,

        // BL
        0xFF,
        0x81,
        0x81,
        0x89,
        0x81,
        0x81,
        0x81,
        0xFF,

        // BR
        0xFF,
        0x81,
        0x81,
        0x91,
        0x81,
        0x81,
        0x81,
        0xFF,

        // =========================================================
        // DESTRUCTIBLE BLOCK 2x2
        // Inspired by the dark brick blocks from Bomb Mania C64
        // =========================================================

        // TL
        0xFF,
        0xAA,
        0xD5,
        0xAA,
        0xFF,
        0x92,
        0x49,
        0x24,

        // TR
        0xFF,
        0x55,
        0xAB,
        0x55,
        0xFF,
        0x49,
        0x92,
        0x24,

        // BL
        0x24,
        0x49,
        0x92,
        0xFF,
        0xAA,
        0xD5,
        0xAA,
        0xFF,

        // BR
        0x24,
        0x92,
        0x49,
        0xFF,
        0x55,
        0xAB,
        0x55,
        0xFF,
};

static const u8 g_Level1WallTileColors[LEVEL1_WALL_TILE_COUNT * LEVEL1_WALL_TILE_SIZE] =
    {
        // =========================================================
        // INDESTRUCTIBLE BLOCK 2x2
        // foreground = black
        // background = light yellow
        // =========================================================

        // TL
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),

        // TR
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),

        // BL
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),

        // BR
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),
        COLOR_MERGE(COLOR_BLACK, COLOR_LIGHT_YELLOW),

        // =========================================================
        // DESTRUCTIBLE BLOCK 2x2
        // foreground alternates between gray / light red fragments
        // background black to keep strong contrast like the original
        // =========================================================

        // TL
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_DARK_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),

        // TR
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_DARK_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),

        // BL
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_DARK_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),

        // BR
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_DARK_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
        COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
        COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
};