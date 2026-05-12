#include "../domain/Bomb.h"
#include "timerController.h"
#include "BombController.h"

void BombController_setBombAsActive(Bomb *bomb) {   
   // bomb->state = READY_BOMB;
   Bomb_setAsReady(bomb);
   TimerController_createCount(bomb->id);
}

void BombController_setBombAsAvailable(Bomb *bomb) {
   Bomb_setAsAvailable(bomb);
   TimerController_removeTimerByTimerId(bomb->id);
}

void BombController_copyLogicPosition(Position *originPosition, Bomb *bomb) {
   bomb->logicPosition.x = originPosition->x;
   bomb->logicPosition.y = originPosition->y;
}

void BombController_copyPixelPosition(Position *originPosition, Bomb *bomb) {
   bomb->pixelPosition.x = originPosition->x;
   bomb->pixelPosition.y = originPosition->y;
}

bool BombController_isBombActive(Bomb *bomb) {   
   return bomb->state == READY_BOMB;
}

void BombController_setBombAsExploited(Bomb *bomb) {
   Bomb_setAsExploited(bomb);
}
