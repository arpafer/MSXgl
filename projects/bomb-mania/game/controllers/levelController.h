
#include "msxgl.h"

#ifndef LEVEL_BLOCK_FLOOR
#define LEVEL_BLOCK_FLOOR          0
#endif
#ifndef LEVEL_BLOCK_INDESTRUCTIBLE
#define LEVEL_BLOCK_INDESTRUCTIBLE 1
#endif
#ifndef LEVEL_BLOCK_DESTRUCTIBLE
#define LEVEL_BLOCK_DESTRUCTIBLE   2
#endif

typedef struct _TileInfoDef {
   const u8* tilePatterns;
   u16 tilePatternsSize;
   const u8* tileColors;
   u16 tileColorsSize;
   const u8* logicMap;
   u8 logicMapCols;
   u8 logicMapRows;
} TileInfo;

const TileInfo* LevelController_getTilesInfo(unsigned char nivelId); 

u8* LevelController_getLogicMap(unsigned char nivelId);
