#include "levelController.h"

#include "../assets/level1/tiles/level1_tileset.h"
#include "../assets/level1/map_level1.h"

static const TileInfo g_Level1TileInfo =
{
    g_Level1TilePatterns,
    sizeof(g_Level1TilePatterns),
    g_Level1TileColors,
    sizeof(g_Level1TileColors),
    g_Level1MapTileMap,
    sizeof(g_Level1MapTileMap),
};

const TileInfo* LevelController_getTilesInfo(unsigned char nivelId)
{
    switch (nivelId)
    {
    case 1:
        return &g_Level1TileInfo;

    default:
        return &g_Level1TileInfo;
    }
}
