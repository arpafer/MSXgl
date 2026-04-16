#pragma once

#include "msxgl.h"
#include "color.h"

#define LEVEL1_FLOOR_TILE_COUNT 1
#define LEVEL1_FLOOR_TILE_SIZE 8

#define LEVEL1_TILE_FLOOR 0

// SCREEN 2 floor tile inspired by the original Bomb-Mania grass/dirt ground.
// Designed to tile cleanly across the arena background.
static const u8 g_Level1FloorTilePatterns[LEVEL1_FLOOR_TILE_COUNT * LEVEL1_FLOOR_TILE_SIZE] =
{
    0x00,
    0x08,
    0x14,
    0x00,
    0x41,
    0x22,
    0x00,
    0x00,
};

static const u8 g_Level1FloorTileColors[LEVEL1_FLOOR_TILE_COUNT * LEVEL1_FLOOR_TILE_SIZE] =
{
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_LIGHT_GREEN, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
    COLOR_MERGE(COLOR_GRAY, COLOR_WHITE),
};
