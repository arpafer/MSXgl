#include "Bomb.h"
#include "Position.h"

bool Bomb_isAvailable(Bomb *bomb) {
    return bomb->state == AVAILABLE_BOMB;
}

void Bomb_copyPosition(Position *originPosition, Position *targetPosition) {
    targetPosition->x = originPosition->x;
    targetPosition->y = originPosition->y;
}

bool Bomb_isExploding(Bomb *bomb) {
   return bomb->state == EXPLODING_BOMB;
}

bool Bomb_isReadyForExplosion(Bomb *bomb) {
    return bomb->state == READY_BOMB;
}

bool Bomb_isExploited(Bomb *bomb) {
    return bomb->state == EXPLOITED_BOMB;
}

void Bomb_setAsReady(Bomb *bomb) {
   bomb->state = READY_BOMB;
}

void Bomb_setExploding(Bomb *bomb) {
   bomb->state = EXPLODING_BOMB;
}

void Bomb_setAsAvailable(Bomb *bomb) {
   bomb->state = AVAILABLE_BOMB;
}

void Bomb_setAsExploited(Bomb *bomb) {
   bomb->state = EXPLOITED_BOMB;
}