#include "msxgl.h"
#include "vdp.h"
#include "level.h"
#include "../controllers/levelController.h"
#include "countDown.h"

#define LEVEL_TILE_BASE_OFFSET 239
#define LEVEL_PHYSICAL_COLS 32
#define LEVEL_PHYSICAL_ROWS 20

#define LEVEL_BLOCK_TILE_COUNT 4
#define LEVEL_LOGICAL_MAX_COLS (LEVEL_PHYSICAL_COLS / 2)
#define LEVEL_LOGICAL_MAX_ROWS (LEVEL_PHYSICAL_ROWS / 2)

void Level_init()
{
    VDP_Initialize();
    VDP_SetMode(VDP_MODE_SCREEN2);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
}

static void Level_loadTileSetToAllBanks(const u8* patterns,
                                        const u8* colors,
                                        u16 tileCount,
                                        u8 offset)
{
    VDP_LoadBankPattern_GM2(patterns, tileCount, 0, offset);
    VDP_LoadBankPattern_GM2(patterns, tileCount, 1, offset);
    VDP_LoadBankPattern_GM2(patterns, tileCount, 2, offset);

    VDP_LoadBankColor_GM2(colors, tileCount, 0, offset);
    VDP_LoadBankColor_GM2(colors, tileCount, 1, offset);
    VDP_LoadBankColor_GM2(colors, tileCount, 2, offset);
}

static u8 Level_getTileBaseFromBlock(u8 blockId)
{
    switch (blockId)
    {
        case LEVEL_BLOCK_INDESTRUCTIBLE:
            return LEVEL_TILE_BASE_OFFSET + 4;

        case LEVEL_BLOCK_DESTRUCTIBLE:
            return LEVEL_TILE_BASE_OFFSET + 8;

        case LEVEL_BLOCK_FLOOR:
        default:
            return LEVEL_TILE_BASE_OFFSET + 0;
    }
}

static void Level_renderBlock2x2(u8 x, u8 y, u8 tileBase)
{
    VDP_Poke_GM2(x,     y,     tileBase + 0);
    VDP_Poke_GM2(x + 1, y,     tileBase + 1);
    VDP_Poke_GM2(x,     y + 1, tileBase + 2);
    VDP_Poke_GM2(x + 1, y + 1, tileBase + 3);
}

static u8 Level_getSafeLogicCols(const TileInfo* tilesInfo)
{
    if (tilesInfo->logicMapCols < LEVEL_LOGICAL_MAX_COLS)
        return tilesInfo->logicMapCols;

    return LEVEL_LOGICAL_MAX_COLS;
}

static u8 Level_getSafeLogicRows(const TileInfo* tilesInfo)
{
    if (tilesInfo->logicMapRows < LEVEL_LOGICAL_MAX_ROWS)
        return tilesInfo->logicMapRows;

    return LEVEL_LOGICAL_MAX_ROWS;
}

static void Level_fillScreenWithFloor(void)
{
    u8 y;
    u8 x;

    for (y = 0; y < LEVEL_PHYSICAL_ROWS; y += 2)
    {
        for (x = 0; x < LEVEL_PHYSICAL_COLS; x += 2)
        {
            Level_renderBlock2x2(x, y, LEVEL_TILE_BASE_OFFSET + 0);
        }
    }
}

static void Level_renderLogicalMap(const TileInfo* tilesInfo)
{
    u8 row;
    u8 maxCols;
    u8 maxRows;

    Level_fillScreenWithFloor();   

    if ((tilesInfo == 0) || (tilesInfo->logicMap == 0))
        return;

    if ((tilesInfo->logicMapCols == 0) || (tilesInfo->logicMapRows == 0))
        return;

    maxCols = Level_getSafeLogicCols(tilesInfo);
    maxRows = Level_getSafeLogicRows(tilesInfo);

    for (row = 0; row < maxRows; row++)
    {
        u8 col;

        for (col = 0; col < maxCols; col++)
        {
            u16 logicIndex = ((u16)row * tilesInfo->logicMapCols) + col;
            u8 blockId = tilesInfo->logicMap[logicIndex];
            u8 tileBase = Level_getTileBaseFromBlock(blockId);

            Level_renderBlock2x2(col * 2, row * 2, tileBase);
        }
    }
}

void Level_loadTiles(unsigned char levelId)
{
    const TileInfo* tilesInfo = LevelController_getTilesInfo(levelId);
    u16 tileCount;

    if (tilesInfo == 0)
        return;

    if ((tilesInfo->tilePatterns == 0) || (tilesInfo->tileColors == 0))
        return;

    tileCount = tilesInfo->tilePatternsSize / 8;

    Level_loadTileSetToAllBanks(tilesInfo->tilePatterns,
                                tilesInfo->tileColors,
                                tileCount,
                                LEVEL_TILE_BASE_OFFSET);

    Level_renderLogicalMap(tilesInfo);
}

void Level_render(unsigned char levelId)
{
    Level_init();
    Level_loadTiles(levelId);

    CountDown_render(levelId);
}