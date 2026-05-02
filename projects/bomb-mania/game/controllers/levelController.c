#include "levelController.h"

#include "../assets/level1/tiles/level1_tileset.h"
#include "../assets/level1/map_level1.h"
#include "../domain/Bomb.h"
#include "../domain/Position.h"
#include "timerController.h"

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

static Bomb g_bombPool[BOMB_NUM_MAX_PER_PLAYER * 4];

void LevelController_initBombPool() {
   for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++) {
       Bomb *_bomb = &g_bombPool[i];
      _bomb->id = 0;
      _bomb->state = AVAILABLE_BOMB;
      _bomb->logicPosition.x = -3;
      _bomb->pixelPosition.y = -3;
      _bomb->pixelPosition.x = -30;
      _bomb->pixelPosition.y = -30;
      _bomb->timeToExplode = BOMB_TIME_TO_EXPLODE;
      _bomb->timeLeft = BOMB_TIME_TO_EXPLODE;
   }
}

Bomb *LevelController_getAvailableBomb() {
    for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++) {
      Bomb *_bomb = &g_bombPool[i];
      if (_bomb->state == AVAILABLE_BOMB) {
        return _bomb;
      }
    }
    return 0;
}

void LevelController_updateBombsState() {
    for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++) {
      Bomb *_bomb = &g_bombPool[i];
      bool _countdownToExplosionEnding = TimerController_countSeconds(_bomb->id, _bomb->timeToExplode);
      if (Bomb_isReadyForExplosion(_bomb) && _countdownToExplosionEnding) {         
         Bomb_setExploding(_bomb);
      }
    }
}

u8* LevelController_getExplodingBombIds() {
    static u8 explodingBombIds[BOMB_NUM_MAX_PER_PLAYER * 4];
    u8 count = 0;
    for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++) {
      Bomb *_bomb = &g_bombPool[i];
      if (_bomb->state == EXPLODING_BOMB) {
         explodingBombIds[count] = _bomb->id;
         count++;
      }
    }
    explodingBombIds[count] = 0xFF; // End of list marker
    return explodingBombIds; 
}

Bomb *LevelController_getBombById(u8 bombId) {
    for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++) {
      Bomb *_bomb = &g_bombPool[i];
      if (_bomb->id == bombId) {
        return _bomb;
      }
    }
    return 0;
}

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

Position* LevelController_getUpFreePositionsFromCurrentPosition(Position *position, u8 scope) {
   return 0;
}

Position* LevelController_getDownFreePositionsFromCurrentPosition(Position *position, u8 scope) {
   return 0;
}

Position* LevelController_getLeftFreePositionsFromCurrentPosition(Position *position, u8 scope) {
    return 0;
}

Position* LevelController_getRightFreePositionsFromCurrentPosition(Position *position, u8 scope) {
    return 0;
}
