#pragma once

#include "msxgl.h"
#include "color.h"

#define LEVEL1_WALL_TILE_COUNT 2
#define LEVEL1_WALL_TILE_SIZE 8

#define LEVEL1_TILE_INDESTRUCTIBLE 0
#define LEVEL1_TILE_DESTRUCTIBLE   1

// SCREEN 2 wall tiles inspired by the 1997 Bomb-Mania title screen.
// Assumption:
// - each map block is rendered as one 8x8 tile
// - the arena uses 32 columns, so these tiles are designed to repeat cleanly
static const u8 g_Level1WallTilePatterns[LEVEL1_WALL_TILE_COUNT * LEVEL1_WALL_TILE_SIZE] =
{
    // Indestructible wall: yellow panel with darker border and rivet-like dots
    0xFF,
    0xC3,
    0x81,
    0xA5,
    0x81,
    0xA5,
    0xC3,
    0xFF,

    // Destructible wall: dark brick with noisy bright fragments
    0xFE,
    0x54,
    0xBA,
    0x10,
    0xEF,
    0x28,
    0xD6,
    0x7C,
};

static const u8 g_Level1WallTileColors[LEVEL1_WALL_TILE_COUNT * LEVEL1_WALL_TILE_SIZE] =
{
    // Indestructible wall colors
    COLOR_MERGE(COLOR_DARK_YELLOW, COLOR_LIGHT_YELLOW),
    COLOR_MERGE(COLOR_DARK_YELLOW, COLOR_LIGHT_YELLOW),
    COLOR_MERGE(COLOR_DARK_YELLOW, COLOR_LIGHT_YELLOW),
    COLOR_MERGE(COLOR_DARK_YELLOW, COLOR_LIGHT_YELLOW),
    COLOR_MERGE(COLOR_DARK_YELLOW, COLOR_LIGHT_YELLOW),
    COLOR_MERGE(COLOR_DARK_YELLOW, COLOR_LIGHT_YELLOW),
    COLOR_MERGE(COLOR_DARK_YELLOW, COLOR_LIGHT_YELLOW),
    COLOR_MERGE(COLOR_DARK_YELLOW, COLOR_LIGHT_YELLOW),

    // Destructible wall colors
    COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
    COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
    COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
    COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
    COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
    COLOR_MERGE(COLOR_LIGHT_RED, COLOR_BLACK),
    COLOR_MERGE(COLOR_GRAY, COLOR_BLACK),
    COLOR_MERGE(COLOR_DARK_RED, COLOR_BLACK),
};
