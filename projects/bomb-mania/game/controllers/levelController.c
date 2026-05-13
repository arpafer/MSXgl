#include "levelController.h"

#include "../assets/level1/tiles/level1_tileset.h"
#include "../assets/level1/map_level1.h"
#include "../domain/Bomb.h"
#include "../domain/Position.h"
#include "timerController.h"
#include "BombController.h"

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

static u8 g_exploitedMapBlocks[LEVEL1_LOGIC_SIZE];
static u8 g_exploitedBlockCount = 0;
static Position g_upFreePositions[LEVEL1_LOGIC_ROWS];
static Position g_downFreePositions[LEVEL1_LOGIC_ROWS];
static Position g_leftFreePositions[LEVEL1_LOGIC_COLS];
static Position g_rightFreePositions[LEVEL1_LOGIC_COLS];

#define FREE_SPACE LEVEL1_BLOCK_FLOOR
#define DESTRUCTIBLE_BLOCK LEVEL1_BLOCK_DESTRUCTIBLE

static void LevelController_clearPositions(Position *positions, u8 count)
{
   u8 i;

   for (i = 0; i < count; i++)
   {
      positions[i].x = INVALID_POSITION;
      positions[i].y = INVALID_POSITION;
   }
}

void LevelController_clearExploitedMapBlocks() {
   for (int i = 0; i < g_exploitedBlockCount; i++)
   {
      Position *position = &g_exploitedMapBlocks[i];
      int index = position->y * LEVEL1_LOGIC_COLS + position->x;
      g_Level1LogicMapCopy[index] = FREE_SPACE;
   }
   g_exploitedBlockCount = 0;
}

bool LevelController_PlayerPositionIsInExplosion(Position *playerPosition, Bomb *bomb) {
   for (int i = 0; i < g_exploitedBlockCount; i++)
   {
      Position *position = &g_exploitedMapBlocks[i];
      if (position->x == playerPosition->x && position->y == playerPosition->y) {
         return TRUE;
      }
   }
   return FALSE;
}

static void LevelController_setPosition(Position *position, u8 x, u8 y)
{
   position->x = x;
   position->y = y;
}

void LevelController_initBombPool()
{
   for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++)
   {
      Bomb *_bomb = &g_bombPool[i];
      _bomb->id = i + ID_BASE_BOMB;
      Bomb_setAsAvailable(_bomb);
   }
}

Bomb *LevelController_getAvailableBomb()
{
   for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++)
   {
      Bomb *_bomb = &g_bombPool[i];
      if (_bomb->state == AVAILABLE_BOMB)
      {
         return _bomb;
      }
   }
   return 0;
}

void LevelController_updateBombsState()
{
   for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++)
   {
      Bomb *_bomb = &g_bombPool[i];
      if (BombController_isBombActive(_bomb))
      {
         bool _countdownToExplosionEnding = TimerController_countSeconds(_bomb->id, _bomb->timeToExplode);
         if (Bomb_isReadyForExplosion(_bomb) && _countdownToExplosionEnding)
         {
            Bomb_setExploding(_bomb);
         }
      }
   }
}

u8 *LevelController_getExplodingBombIds()
{
   static u8 explodingBombIds[BOMB_NUM_MAX_PER_PLAYER * 4];
   u8 count = 0;
   for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++)
   {
      Bomb *_bomb = &g_bombPool[i];
      if (_bomb->state == EXPLODING_BOMB)
      {
         explodingBombIds[count] = _bomb->id;
         count++;
      }
   }
   explodingBombIds[count] = 0xFF; // End of list marker
   return explodingBombIds;
}

Bomb *LevelController_getBombById(u8 bombId)
{
   for (int i = 0; i < BOMB_NUM_MAX_PER_PLAYER * 4; i++)
   {
      Bomb *_bomb = &g_bombPool[i];
      if (_bomb->id == bombId)
      {
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

const TileInfo *LevelController_getTilesInfo(unsigned char nivelId)
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

u8 *LevelController_getLogicMap(unsigned char nivelId)
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

Position *LevelController_getUpFreePositionsFromCurrentPosition(Position *position, u8 scope)
{
   int previousRow = position->y - 1;
   int currentCol = position->x;
   bool _canAdvance = TRUE;
   int _positionIndex = 0;

   LevelController_clearPositions(g_upFreePositions, LEVEL1_LOGIC_ROWS);

   while (_canAdvance && (previousRow > 0) && (position->y - previousRow <= scope))
   {
      int i = previousRow * LEVEL1_LOGIC_COLS + currentCol;
      if (g_Level1LogicMapCopy[i] == FREE_SPACE)
      {
         LevelController_setPosition(&g_upFreePositions[_positionIndex], currentCol, previousRow);
         LevelController_setPosition(&g_exploitedMapBlocks[g_exploitedBlockCount], currentCol, previousRow);
         g_exploitedBlockCount++;
         _positionIndex++;         
      }
      else if (g_Level1LogicMapCopy[i] == DESTRUCTIBLE_BLOCK)
      {
         LevelController_setPosition(&g_upFreePositions[g_exploitedBlockCount], currentCol, previousRow);
         LevelController_setPosition(&g_exploitedMapBlocks[g_exploitedBlockCount], currentCol, previousRow);
         g_exploitedBlockCount++;
         _positionIndex++;         
         _canAdvance = FALSE;
         g_Level1LogicMapCopy[i] = FREE_SPACE;
      }
      else
      {
         _canAdvance = FALSE;
      }
      previousRow--;
   }
   return g_upFreePositions;
}

Position *LevelController_getDownFreePositionsFromCurrentPosition(Position *position, u8 scope)
{
   int nextRow = position->y + 1;
   int currentCol = position->x;
   bool _canAdvance = TRUE;
   int _positionIndex = 0;

   LevelController_clearPositions(g_downFreePositions, LEVEL1_LOGIC_ROWS);

   while (_canAdvance && (nextRow < LEVEL1_LOGIC_ROWS - 1) && (nextRow - position->y <= scope))
   {
      int i = nextRow * LEVEL1_LOGIC_COLS + currentCol;
      if (g_Level1LogicMapCopy[i] == FREE_SPACE)
      {
         LevelController_setPosition(&g_downFreePositions[_positionIndex], currentCol, nextRow);
         LevelController_setPosition(&g_exploitedMapBlocks[g_exploitedBlockCount], currentCol, nextRow);
         g_exploitedBlockCount++;
         _positionIndex++;
      }
      else if (g_Level1LogicMapCopy[i] == DESTRUCTIBLE_BLOCK)
      {
         LevelController_setPosition(&g_downFreePositions[_positionIndex], currentCol, nextRow);
         LevelController_setPosition(&g_exploitedMapBlocks[g_exploitedBlockCount], currentCol, nextRow);
         g_exploitedBlockCount++;
         _positionIndex++;
         _canAdvance = FALSE;
         g_Level1LogicMapCopy[i] = FREE_SPACE;
      }
      else
      {
         _canAdvance = FALSE;
      }
      nextRow++;
   }
   return g_downFreePositions;
}

Position *LevelController_getLeftFreePositionsFromCurrentPosition(Position *position, u8 scope)
{
   int previousCol = position->x - 1;
   int currentRow = position->y;
   bool _canAdvance = TRUE;
   int _positionIndex = 0;

   LevelController_clearPositions(g_leftFreePositions, LEVEL1_LOGIC_COLS);

   while (_canAdvance && (previousCol > 0) && (position->x - previousCol <= scope))
   {
      int i = currentRow * LEVEL1_LOGIC_COLS + previousCol;
      if (g_Level1LogicMapCopy[i] == FREE_SPACE)
      {
         LevelController_setPosition(&g_leftFreePositions[_positionIndex], previousCol, currentRow);
         LevelController_setPosition(&g_exploitedMapBlocks[g_exploitedBlockCount], previousCol, currentRow);
         g_exploitedBlockCount++;
         _positionIndex++;
      }
      else if (g_Level1LogicMapCopy[i] == DESTRUCTIBLE_BLOCK)
      {
         LevelController_setPosition(&g_leftFreePositions[_positionIndex], previousCol, currentRow);
         LevelController_setPosition(&g_exploitedMapBlocks[g_exploitedBlockCount], previousCol, currentRow);
         g_exploitedBlockCount++;
         _positionIndex++;
         _canAdvance = FALSE;
         g_Level1LogicMapCopy[i] = FREE_SPACE;
      }
      else
      {
         _canAdvance = FALSE;
      }
      previousCol--;
   }
   return g_leftFreePositions;
}

Position *LevelController_getRightFreePositionsFromCurrentPosition(Position *position, u8 scope)
{
   int nextCol = position->x + 1;
   int currentRow = position->y;
   bool _canAdvance = TRUE;
   int _positionIndex = 0;

   LevelController_clearPositions(g_rightFreePositions, LEVEL1_LOGIC_COLS);

   while (_canAdvance && (nextCol < LEVEL1_LOGIC_COLS - 1) && (nextCol - position->x <= scope))
   {
      int i = currentRow * LEVEL1_LOGIC_COLS + nextCol;
      if (g_Level1LogicMapCopy[i] == FREE_SPACE)
      {
         LevelController_setPosition(&g_rightFreePositions[_positionIndex], nextCol, currentRow);
         LevelController_setPosition(&g_exploitedMapBlocks[g_exploitedBlockCount], nextCol, currentRow);
         g_exploitedBlockCount++;
         _positionIndex++;
      }
      else if (g_Level1LogicMapCopy[i] == DESTRUCTIBLE_BLOCK)
      {
         LevelController_setPosition(&g_rightFreePositions[_positionIndex], nextCol, currentRow);
         LevelController_setPosition(&g_exploitedMapBlocks[g_exploitedBlockCount], nextCol, currentRow);
         g_exploitedBlockCount++;
         _positionIndex++;
         _canAdvance = FALSE;
         g_Level1LogicMapCopy[i] = FREE_SPACE;
      }
      else
      {
         _canAdvance = FALSE;
      }
      nextCol++;
   }
   return g_rightFreePositions;
}
