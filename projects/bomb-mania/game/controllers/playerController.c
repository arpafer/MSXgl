#include "msxgl.h"
#include "playerController.h"
#include "../domain/Player.h"
#include "../domain/Direction.h"

#ifndef LEVEL_LOGICAL_COLS  
#define LEVEL_LOGICAL_COLS 16
#endif

#ifndef LEVEL_LOGICAL_ROWS
#define LEVEL_LOGICAL_ROWS 10
#endif

#ifndef LEVEL_BLOCK_FLOOR
#define LEVEL_BLOCK_FLOOR          0
#endif
#ifndef LEVEL_BLOCK_INDESTRUCTIBLE
#define LEVEL_BLOCK_INDESTRUCTIBLE 1
#endif
#ifndef LEVEL_BLOCK_DESTRUCTIBLE
#define LEVEL_BLOCK_DESTRUCTIBLE   2
#endif

static Player players[4];
static Position g_playerInitialPositions[4];

static Direction PlayerController_getArrowKeyboardDirection(void)
{
    if (Keyboard_IsKeyPressed(KEY_UP))
        return DIRECTION_UP;

    if (Keyboard_IsKeyPressed(KEY_RIGHT))
        return DIRECTION_RIGHT;

    if (Keyboard_IsKeyPressed(KEY_DOWN))
        return DIRECTION_DOWN;

    if (Keyboard_IsKeyPressed(KEY_LEFT))
        return DIRECTION_LEFT;

    return DIRECTION_NONE;
}

static Direction PlayerController_getAwszKeyboardDirection(void)
{
    if (Keyboard_IsKeyPressed(KEY_W))
        return DIRECTION_UP;

    if (Keyboard_IsKeyPressed(KEY_S))
        return DIRECTION_RIGHT;

    if (Keyboard_IsKeyPressed(KEY_Z))
        return DIRECTION_DOWN;

    if (Keyboard_IsKeyPressed(KEY_A))
        return DIRECTION_LEFT;

    return DIRECTION_NONE;
}

static Position *PlayerController_getPlayer1InitialPosition()
{
    Position *position = &g_playerInitialPositions[0];
    position->y = 1;
    position->x = 1;
    return position;
}

static Position *PlayerController_getPlayer2InitialPosition()
{
    Position *position = &g_playerInitialPositions[1];
    position->y = LEVEL_LOGICAL_ROWS - 2;
    position->x = LEVEL_LOGICAL_COLS - 2;
    return position;
}

static Position *PlayerController_getPlayer3InitialPosition()
{
    Position *position = &g_playerInitialPositions[2];
    position->y = 1;
    position->x = LEVEL_LOGICAL_COLS - 2;
    return position;
}

static Position *PlayerController_getPlayer4InitialPosition()
{
    Position *position = &g_playerInitialPositions[3];
    position->y = LEVEL_LOGICAL_ROWS - 2;
    position->x = 1;
    return position;
}

Player *PlayerController_init(u8 playerId)
{
    Player *player = NULL;
    if (playerId == 1)
    {        
        player = &players[playerId - 1];
        Player_init(player, playerId, 1, PlayerController_getPlayer1InitialPosition(), SPRITE_SCALE_16);

    } else if (playerId == 2) {
        player = &players[playerId - 1];
        Player_init(player, playerId, 1, PlayerController_getPlayer2InitialPosition(), SPRITE_SCALE_16);

    } else if (playerId == 3) {
        player = &players[playerId - 1];
        Player_init(player, playerId, 1, PlayerController_getPlayer3InitialPosition(), SPRITE_SCALE_16);

    } else if (playerId == 4) {
        player = &players[playerId - 1];
        Player_init(player, playerId, 1, PlayerController_getPlayer4InitialPosition(), SPRITE_SCALE_16);
    }
    return player;
}

bool PlayerController_canMoveTo(u8 row, u8 col, u8* logicMap) {
   return logicMap[((row) * LEVEL_LOGICAL_COLS) + (col)] == LEVEL_BLOCK_FLOOR;
}

void PlayerController_updateSpritePixelPosition(u8 playerId, Direction direction, u8 *logicMap) {
    Player *player = &players[playerId - 1];
    u8 row = player->logicPosition->y;
    u8 col = player->logicPosition->x;
    if (direction == DIRECTION_RIGHT && PlayerController_canMoveTo(row, col + 1, logicMap)) {        
        Player_moveRight(player);
    } else if (direction == DIRECTION_LEFT && PlayerController_canMoveTo(row, col - 1, logicMap)) {
        Player_moveLeft(player);
    } else if (direction == DIRECTION_UP && PlayerController_canMoveTo(row - 1, col, logicMap)) {
        Player_moveUp(player);
    } else if (direction == DIRECTION_DOWN && PlayerController_canMoveTo(row + 1, col, logicMap)) {
        Player_moveDown(player);
    }
} 

Direction PlayerController_manageMove(u8 playerId, Player **player, u8 *logicMap)
{
    if (playerId == 1)
    {
        Direction direction = PlayerController_getArrowKeyboardDirection();
        PlayerController_updateSpritePixelPosition(playerId, direction, logicMap);
        *player = &players[playerId - 1];
        return direction;
    } else if (playerId == 2) {
        Direction direction = PlayerController_getAwszKeyboardDirection();
        PlayerController_updateSpritePixelPosition(playerId, direction, logicMap);
        *player = &players[playerId - 1];
        return direction;
    }
    return DIRECTION_NONE;
}
