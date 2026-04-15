
#include "msxgl.h"

typedef struct _TileInfoDef {
   const u8* tilePatterns;
   u16 tilePatternsSize;
   const u8* tileColors;
   u16 tileColorsSize;
   const u8* tileMap;
   u16 tileMapSize;
} TileInfo;

const TileInfo* LevelController_getTilesInfo(unsigned char nivelId); 