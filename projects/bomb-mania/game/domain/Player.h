#include "msxgl.h"

#include "Position.h"

#ifndef SPRITE_SCALE_8
#define SPRITE_SCALE_8 8
#endif

#ifndef SPRITE_SCALE_16
#define SPRITE_SCALE_16 16
#endif


#ifndef PLAYER_STRUCT
#define PLAYER_STRUCT
typedef struct PlayerStruct
{
    u8 id;
    u8 velocity;
    Position *logicPosition;
    Position *pixelPosition;
} Player;

#endif

void Player_init(Player *player, u8 playerId, u8 velocity, Position *position, u8 scaleType);

bool Player_isDie(Player *player);
bool Player_isIdle(Player *player);
bool Player_isMoving(Player *player);   

void Player_moveRight(Player *player);
void Player_moveLeft(Player *player);
void Player_moveUp(Player *player);
void Player_moveDown(Player *player);
