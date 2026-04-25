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

void PlayerController_updateSpritePixelPosition(u8 playerId, Direction direction) {
    if (direction == DIRECTION_RIGHT) {        
        Player_moveRight(&players[playerId - 1]);
    } else if (direction == DIRECTION_LEFT) {
        Player_moveLeft(&players[playerId - 1]);
    } else if (direction == DIRECTION_UP) {
        Player_moveUp(&players[playerId - 1]);
    } else if (direction == DIRECTION_DOWN) {
        Player_moveDown(&players[playerId - 1]);
    }
} 

Player *PlayerController_manageMove(u8 playerId)
{
    if (playerId == 1)
    {
        Direction direction = PlayerController_getArrowKeyboardDirection();
        PlayerController_updateSpritePixelPosition(playerId, direction);
        return &players[playerId - 1];
    }
    return 0;
}
