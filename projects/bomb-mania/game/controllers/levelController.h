
#include "msxgl.h"

#include "../domain/Bomb.h"
#include "../domain/Position.h"

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

void LevelController_initBombPool();

const TileInfo* LevelController_getTilesInfo(unsigned char nivelId); 

u8* LevelController_getLogicMap(unsigned char nivelId);

Bomb *LevelController_getAvailableBomb();

void LevelController_updateBombsState();

u8* LevelController_getExplodingBombIds();

Bomb *LevelController_getBombById(u8 bombId);

Position* LevelController_getUpFreePositionsFromCurrentPosition(Position *position, u8 scope);

Position* LevelController_getDownFreePositionsFromCurrentPosition(Position *position, u8 scope);

Position* LevelController_getLeftFreePositionsFromCurrentPosition(Position *position, u8 scope);

Position* LevelController_getRightFreePositionsFromCurrentPosition(Position *position, u8 scope);

void LevelController_clearExploitedMapBlocks();

bool LevelController_PlayerPositionIsInExplosion(Position *playerPosition, Bomb *bomb);
