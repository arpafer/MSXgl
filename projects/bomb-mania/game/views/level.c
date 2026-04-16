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

static void Level_loadTileSetToAllBanks(const u8* patterns, const u8* colors, u16 tileCount, u8 offset)
{
    VDP_LoadBankPattern_GM2(patterns, tileCount, 0, offset);
    VDP_LoadBankPattern_GM2(patterns, tileCount, 1, offset);
    VDP_LoadBankPattern_GM2(patterns, tileCount, 2, offset);

    VDP_LoadBankColor_GM2(colors, tileCount, 0, offset);
    VDP_LoadBankColor_GM2(colors, tileCount, 1, offset);
    VDP_LoadBankColor_GM2(colors, tileCount, 2, offset);
}

void Level_loadTiles(unsigned char levelId)
{
    const TileInfo* tilesInfo = LevelController_getTilesInfo(levelId);

    if (tilesInfo == 0)
        return;

    if ((tilesInfo->tilePatterns != 0) && (tilesInfo->tileColors != 0))
        Level_loadTileSetToAllBanks(tilesInfo->tilePatterns,
                                    tilesInfo->tileColors,
                                    tilesInfo->tilePatternsSize / 8,
                                    239);

    if ((tilesInfo->tileMap != 0) && (tilesInfo->tileMapSize != 0))
        VDP_WriteVRAM(tilesInfo->tileMap, VDP_G2_ADDR_NT, 0, tilesInfo->tileMapSize);
}

void Level_render(unsigned char levelId)
{
    Level_init();
    Level_loadTiles(levelId);
}
