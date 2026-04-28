#pragma once

#include "msxgl.h"
#include "color.h"

#define BOMB_TILE_COUNT 4
#define BOMB_TILE_SIZE 8

#define BOMB_TILE_TL 0
#define BOMB_TILE_TR 1
#define BOMB_TILE_BL 2
#define BOMB_TILE_BR 3

// SCREEN 2 bomb tile inspired by the Bomb-Mania C64 bombs.
// Each logical bomb is a 16x16 block made of 2x2 hardware tiles.
static const u8 g_BombTilePatterns[BOMB_TILE_COUNT * BOMB_TILE_SIZE] =
{
    // =========================================================
    // BOMB 2x2
    // compact black body with a small gray fuse on the upper right
    // =========================================================

    // TL
    0x00,
    0x00,
    0x00,
    0x00,
    0x03,
    0x0F,
    0x1F,
    0x1F,

    // TR
    0x00,
    0x10,
    0x38,
    0x74,
    0xE0,
    0xF0,
    0xF8,
    0xF8,

    // BL
    0x1F,
    0x1F,
    0x0F,
    0x0F,
    0x03,
    0x00,
    0x00,
    0x00,

    // BR
    0xF8,
    0xF8,
    0xF0,
    0xF0,
    0xE0,
    0x00,
    0x00,
    0x00,
};

static const u8 g_BombTileColors[BOMB_TILE_COUNT * BOMB_TILE_SIZE] =
{
    // =========================================================
    // BOMB 2x2 COLORS
    // foreground = black body / gray fuse
    // background = white, matching the current pale floor tiles
    // =========================================================

    // TL
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),

    // TR
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),

    // BL
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),

    // BR
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
    COLOR_MERGE(COLOR_BLACK, COLOR_WHITE),
};
