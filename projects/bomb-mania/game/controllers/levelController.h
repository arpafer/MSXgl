
#include "msxgl.h"

#define LEVEL_BLOCK_FLOOR          0
#define LEVEL_BLOCK_INDESTRUCTIBLE 1
#define LEVEL_BLOCK_DESTRUCTIBLE   2

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
