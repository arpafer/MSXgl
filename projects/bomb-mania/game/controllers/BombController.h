
#pragma once

#include "../domain/Bomb.h"

#ifndef ID_BASE_BOMB
    #define ID_BASE_BOMB 3
#endif

void BombController_setBombAsActive(Bomb *bomb);

void BombController_setBombAsAvailable(Bomb *bomb);

void BombController_copyLogicPosition(Position *originPosition, Bomb *bomb);

void BombController_copyPixelPosition(Position *originPosition, Bomb *bomb);

bool BombController_isBombActive(Bomb *bomb);

void BombController_setBombAsExploited(Bomb *bomb);