
#pragma once

#include "../domain/Bomb.h"

void BombController_setBombAsActive(Bomb *bomb);

void BombController_copyLogicPosition(Position *originPosition, Bomb *bomb);

void BombController_copyPixelPosition(Position *originPosition, Bomb *bomb);
