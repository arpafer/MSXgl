#include "msxgl.h"
#include "vdp.h"
#include "level.h"
#include "../controllers/levelController.h"

void Level_init()
{
    VDP_Initialize();
    VDP_SetMode(VDP_MODE_SCREEN2);
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
}

void Level_loadTiles(unsigned char levelId)
{
    VDP_SetPatternTable(VDP_G2_ADDR_PT);
    VDP_SetColorTable(VDP_G2_ADDR_CT);
    VDP_SetLayoutTable(VDP_G2_ADDR_NT);

    const TileInfo* tilesInfo = LevelController_getTilesInfo(levelId);
    VDP_WriteVRAM(tilesInfo->tilePatterns, VDP_G2_ADDR_PT, 0, tilesInfo->tilePatternsSize);
    VDP_WriteVRAM(tilesInfo->tileColors, VDP_G2_ADDR_CT, 0, tilesInfo->tileColorsSize);
    VDP_WriteVRAM(tilesInfo->tileMap, VDP_G2_ADDR_NT, 0, tilesInfo->tileMapSize);
}

void Level_render(unsigned char levelId)
{
    Level_init();
    Level_loadTiles(levelId);
}