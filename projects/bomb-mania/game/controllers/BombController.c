#include "../domain/Bomb.h"

void BombController_setBombAsActive(Bomb *bomb) {
   bomb->state = READY_BOMB;
}

void BombController_copyLogicPosition(Position *originPosition, Bomb *bomb) {
   bomb->logicPosition.x = originPosition->x;
   bomb->logicPosition.y = originPosition->y;
}

void BombController_copyPixelPosition(Position *originPosition, Bomb *bomb) {
   bomb->pixelPosition.x = originPosition->x;
   bomb->pixelPosition.y = originPosition->y;
}
