#include "../assets/bombTiles/bomb_tile.h"
#include "../domain/Bomb.h"
#include "../controllers/BombController.h"
#include "vdp.h"

#define BOMB_TILE_BASE_OFFSET 251
#define BOMB_LOGIC_TO_TILE_SCALE 2

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
