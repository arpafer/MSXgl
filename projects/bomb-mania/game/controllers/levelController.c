#include "levelController.h"

#include "../assets/level1/tiles/level1_tileset.h"
#include "../assets/level1/map_level1.h"

static u8 g_Level1LogicMapCopy[LEVEL1_LOGIC_SIZE];
static bool g_Level1LogicMapCopyInitialized = FALSE;

static const TileInfo g_Level1TileInfo =
{
    g_Level1TilePatterns,
    sizeof(g_Level1TilePatterns),
    g_Level1TileColors,
    sizeof(g_Level1TileColors),
    g_Level1LogicMapCopy,
    LEVEL1_LOGIC_COLS,
    LEVEL1_LOGIC_ROWS,
};

static void LevelController_initLevel1LogicMapCopy(void)
{
    if (g_Level1LogicMapCopyInitialized)
        return;

    Mem_Copy(g_Level1LogicMap, g_Level1LogicMapCopy, LEVEL1_LOGIC_SIZE);
    g_Level1LogicMapCopyInitialized = TRUE;
}

const TileInfo* LevelController_getTilesInfo(unsigned char nivelId)
{
    switch (nivelId)
    {
    case 1:
        LevelController_initLevel1LogicMapCopy();
        return &g_Level1TileInfo;

    default:
        LevelController_initLevel1LogicMapCopy();
        return &g_Level1TileInfo;
    }
}

u8* LevelController_getLogicMap(unsigned char nivelId)
{
    switch (nivelId)
    {
    case 1:
        LevelController_initLevel1LogicMapCopy();
        return g_Level1LogicMapCopy;

    default:
        LevelController_initLevel1LogicMapCopy();
        return g_Level1LogicMapCopy;
    }
}
