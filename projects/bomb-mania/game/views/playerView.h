#include "../domain/Bomb.h"

void Player_render(u8 playerId);

void Player_manageMove(u8 playerId, u8* logicMap);

bool Player_hasShot(u8 playerId);

void PlayerView_renderBomb(Bomb *bomb, u8 playerId);

void PlayerView_updateBombsStateOfPlayer(u8 playerId);