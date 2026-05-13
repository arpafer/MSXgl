#include "msxgl.h"
#include "../domain/Direction.h"
#include "../domain/Player.h"

Player *PlayerController_init(u8 playerId);

Direction PlayerController_manageMove(u8 playerId, Player **player, u8* logicMap);

bool PlayerController_hasShot(u8 playerId, Player **player);

Player *PlayerController_getPlayerWithId(u8 playerId);

void PlayerController_removeBombFromPlayer(Player *player, u8 bombId);

void PlayerController_setPlayerAsDead(Player *player);

bool PlayerController_isAlive(Player *player);