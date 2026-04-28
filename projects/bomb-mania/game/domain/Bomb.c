#include "Bomb.h"
#include "Position.h"

bool Bomb_isAvailable(Bomb *bomb) {
    return bomb->state == AVAILABLE_BOMB;
}

void Bomb_copyPosition(Position *originPosition, Position *targetPosition) {
    targetPosition->x = originPosition->x;
    targetPosition->y = originPosition->y;
}