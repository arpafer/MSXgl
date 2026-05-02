#include "../assets/bombTiles/bomb_tile.h"
#include "../assets/bombTiles/explosion_tile.h"
#include "../domain/Bomb.h"
#include "../controllers/BombController.h"
#include "../controllers/timerController.h"
#include "../controllers/levelController.h"
#include "vdp.h"

#define BOMB_TILE_BASE_OFFSET 251
#define BOMB_LOGIC_TO_TILE_SCALE 2
#define BOMB_EXPLOSION_TIMER_OFFSET 64
#define BOMB_EXPLOSION_SECONDS 1
#define BOMB_EXPLOSION_MAX_BOMBS 16
#define BOMB_EXPLOSION_INVALID_POSITION 0xFF

#ifndef LEVEL_PHYSICAL_COLS
  #define LEVEL_PHYSICAL_COLS 32
  #define LEVEL_LOGICAL_MAX_COLS (LEVEL_PHYSICAL_COLS / 2)
#endif

#ifndef LEVEL_PHYSICAL_ROWS
  #define LEVEL_PHYSICAL_ROWS 20
  #define LEVEL_LOGICAL_MAX_ROWS (LEVEL_PHYSICAL_ROWS / 2)
#endif



static bool g_BombExplosionStarted[BOMB_EXPLOSION_MAX_BOMBS];
static u8 g_BombExplosionTicks[BOMB_EXPLOSION_MAX_BOMBS];

static void BombView_loadTilesToAllBanks(void)
{
   VDP_LoadBankPattern_GM2(g_BombTilePatterns, BOMB_TILE_COUNT, 0, BOMB_TILE_BASE_OFFSET);
   VDP_LoadBankPattern_GM2(g_BombTilePatterns, BOMB_TILE_COUNT, 1, BOMB_TILE_BASE_OFFSET);
   VDP_LoadBankPattern_GM2(g_BombTilePatterns, BOMB_TILE_COUNT, 2, BOMB_TILE_BASE_OFFSET);

   VDP_LoadBankColor_GM2(g_BombTileColors, BOMB_TILE_COUNT, 0, BOMB_TILE_BASE_OFFSET);
   VDP_LoadBankColor_GM2(g_BombTileColors, BOMB_TILE_COUNT, 1, BOMB_TILE_BASE_OFFSET);
   VDP_LoadBankColor_GM2(g_BombTileColors, BOMB_TILE_COUNT, 2, BOMB_TILE_BASE_OFFSET);
}

static void BombView_renderTile2x2(u8 x, u8 y)
{
   VDP_Poke_GM2(x, y, BOMB_TILE_BASE_OFFSET + BOMB_TILE_TL);
   VDP_Poke_GM2(x + 1, y, BOMB_TILE_BASE_OFFSET + BOMB_TILE_TR);
   VDP_Poke_GM2(x, y + 1, BOMB_TILE_BASE_OFFSET + BOMB_TILE_BL);
   VDP_Poke_GM2(x + 1, y + 1, BOMB_TILE_BASE_OFFSET + BOMB_TILE_BR);
}

static void BombView_loadExplosionFrame(u8 frame)
{
   const u8 *patterns = g_ExplosionTilePatterns + ((u16)frame * EXPLOSION_TILES_PER_FRAME * EXPLOSION_TILE_SIZE);
   const u8 *colors = g_ExplosionTileColors + ((u16)frame * EXPLOSION_TILES_PER_FRAME * EXPLOSION_TILE_SIZE);

   VDP_LoadBankPattern_GM2(patterns, EXPLOSION_TILES_PER_FRAME, 0, BOMB_TILE_BASE_OFFSET);
   VDP_LoadBankPattern_GM2(patterns, EXPLOSION_TILES_PER_FRAME, 1, BOMB_TILE_BASE_OFFSET);
   VDP_LoadBankPattern_GM2(patterns, EXPLOSION_TILES_PER_FRAME, 2, BOMB_TILE_BASE_OFFSET);

   VDP_LoadBankColor_GM2(colors, EXPLOSION_TILES_PER_FRAME, 0, BOMB_TILE_BASE_OFFSET);
   VDP_LoadBankColor_GM2(colors, EXPLOSION_TILES_PER_FRAME, 1, BOMB_TILE_BASE_OFFSET);
   VDP_LoadBankColor_GM2(colors, EXPLOSION_TILES_PER_FRAME, 2, BOMB_TILE_BASE_OFFSET);
}

static void BombView_renderExplosionTile(Position *position)
{
   BombView_renderTile2x2(
      position->x * BOMB_LOGIC_TO_TILE_SCALE,
      position->y * BOMB_LOGIC_TO_TILE_SCALE);
}

static void BombView_renderExplosionLine(Position *positions, u8 scope)
{
   u8 i;

   if (positions == 0)
      return;

   for (i = 0; i < scope; i++)
   {
      if ((positions[i].x != BOMB_EXPLOSION_INVALID_POSITION) &&
          (positions[i].y != BOMB_EXPLOSION_INVALID_POSITION))
      {
         BombView_renderExplosionTile(&positions[i]);
      }
   }
}

static u8 BombView_getExplosionFrame(u8 bombIndex)
{
   u8 ticksPerFrame = Sys_Is60Hz() ? 15 : 13;
   u8 frame = g_BombExplosionTicks[bombIndex] / ticksPerFrame;

   if (frame >= EXPLOSION_TILE_FRAME_COUNT)
      return EXPLOSION_TILE_FRAME_COUNT - 1;

   return frame;
}

void BombView_render(Bomb *bomb)
{
   u8 tileX;
   u8 tileY;

   if (bomb == 0)
      return;

   BombView_loadTilesToAllBanks();

   tileX = bomb->logicPosition.x * BOMB_LOGIC_TO_TILE_SCALE;
   tileY = bomb->logicPosition.y * BOMB_LOGIC_TO_TILE_SCALE;

   BombView_renderTile2x2(tileX, tileY);

   BombController_setBombAsActive(bomb);
}

void BombView_renderExplosion(Bomb *bomb, u8 scope)
{
   u8 bombIndex;
   u8 timerId;
   u8 frame;

   Position *upPositions;
   Position *downPositions;
   Position *leftPositions;
   Position *rightPositions;

   if (bomb == 0)
      return;

   bombIndex = bomb->id & 0x0F;
   timerId = BOMB_EXPLOSION_TIMER_OFFSET + bomb->id;

   if (!g_BombExplosionStarted[bombIndex])
   {
      TimerController_createCount(timerId);
      g_BombExplosionStarted[bombIndex] = TRUE;
      g_BombExplosionTicks[bombIndex] = 0;
   }

   if (TimerController_countSeconds(timerId, BOMB_EXPLOSION_SECONDS))
   {
      TimerController_removeTimerByTimerId(timerId);
      g_BombExplosionStarted[bombIndex] = FALSE;
      BombController_setBombAsExploited(bomb);
      return;
   }

   frame = BombView_getExplosionFrame(bombIndex);
   BombView_loadExplosionFrame(frame);

   upPositions = LevelController_getUpFreePositionsFromCurrentPosition(&(bomb->logicPosition), scope);
   downPositions = LevelController_getDownFreePositionsFromCurrentPosition(&(bomb->logicPosition), scope);
   leftPositions = LevelController_getLeftFreePositionsFromCurrentPosition(&(bomb->logicPosition), scope);
   rightPositions = LevelController_getRightFreePositionsFromCurrentPosition(&(bomb->logicPosition), scope);

   BombView_renderExplosionTile(&(bomb->logicPosition));
   BombView_renderExplosionLine(upPositions, scope);
   BombView_renderExplosionLine(downPositions, scope);
   BombView_renderExplosionLine(leftPositions, scope);
   BombView_renderExplosionLine(rightPositions, scope);

   g_BombExplosionTicks[bombIndex]++;
}
