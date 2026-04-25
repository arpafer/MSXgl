#include "Player.h"
#include "Position.h"

static Position g_playerPixelPositions[4];

static Position *Player_getInitialPixelPosition(u8 playerId, Position *logicPosition, u8 scaleFactor) {
    Position *pixelPosition = &g_playerPixelPositions[playerId - 1];
    pixelPosition->x = logicPosition->x * scaleFactor;
    pixelPosition->y = logicPosition->y * scaleFactor;
    return pixelPosition;
}

void Player_init(Player *player, u8 playerId, u8 velocity, Position *position, u8 scaleType) {
    player->id = playerId;
    player->velocity = velocity;
    player->logicPosition = position;
    player->pixelPosition = Player_getInitialPixelPosition(playerId, position, scaleType);
}

bool Player_isDie(Player *player) {
    return TRUE;
}
bool Player_isIdle(Player *player) {
    return TRUE;
}
bool Player_isMoving(Player *player) {
    return TRUE;
}

void Player_moveRight(Player *player) {
   player->pixelPosition->x++;
}

void Player_moveLeft(Player *player) {
   player->pixelPosition->x--;
}

void Player_moveUp(Player *player) {
   player->pixelPosition->y--;
}

void Player_moveDown(Player *player) {
   player->pixelPosition->y++;
}
