#include "msxgl.h"

#include "Position.h"

typedef struct PlayerStruct
{
    u8 id;
    u8 velocity;
    Position position;
} Player;

extern Player players[4];

bool Player_init(Player* player, u8 id, u8 velocity, Position position);

bool Player_isDie(Player* player);
bool Player_isIdle(Player* player);
bool Player_isMoving(Player* player);   