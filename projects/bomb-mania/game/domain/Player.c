#include "Player.h"
#include "Position.h"

static Position g_playerPixelPositions[4];

static Position *Player_getInitialPixelPosition(u8 playerId, Position *logicPosition, u8 scaleFactor)
{
    Position *pixelPosition = &g_playerPixelPositions[playerId - 1];
    pixelPosition->x = logicPosition->x * scaleFactor;
    pixelPosition->y = logicPosition->y * scaleFactor;
    return pixelPosition;
}

void Player_init(Player *player, u8 playerId, u8 velocity, Position *position, u8 scaleType)
{

    player->id = playerId;
    player->velocity = velocity;
    player->logicPosition = position;
    player->scaleFactor = scaleType;
    player->bombCount = 0;
    player->pixelPosition = Player_getInitialPixelPosition(playerId, position, scaleType);
    player->isAlive = TRUE;
}

bool Player_isDie(Player *player)
{
    return !player->isAlive;
}
bool Player_isIdle(Player *player)
{
    return TRUE;
}

bool Player_isMoving(Player *player)
{
    return TRUE;
}

static void Player_updateLogicPosition(Player *player)
{
    player->logicPosition->x = player->pixelPosition->x / player->scaleFactor;
    player->logicPosition->y = player->pixelPosition->y / player->scaleFactor;
}

void Player_moveRight(Player *player)
{
    player->pixelPosition->x += player->velocity;
    Player_updateLogicPosition(player);
}

void Player_moveLeft(Player *player)
{
    player->pixelPosition->x -= player->velocity;
    Player_updateLogicPosition(player);
}

void Player_moveUp(Player *player)
{
    player->pixelPosition->y -= player->velocity;
    Player_updateLogicPosition(player);
}

void Player_moveDown(Player *player)
{
    player->pixelPosition->y += player->velocity;
    Player_updateLogicPosition(player);
}

void Player_setBombPlaced(Player *player, u8 bombId)
{
    if (player->bombCount >= MAX_BOMB_PER_PLAYER)
    {
        return;
    }

    player->BombIds[player->bombCount] = bombId;
    player->bombCount++;
}

bool Player_canPlaceBomb(Player *player) {
    return player->bombCount < MAX_BOMB_PER_PLAYER;
}
