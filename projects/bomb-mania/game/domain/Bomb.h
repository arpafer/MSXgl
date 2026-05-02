#include "msxgl.h"
#include "Position.h"

#ifndef BOMB_TIME_TO_EXPLODE
  #define BOMB_TIME_TO_EXPLODE 3
#endif

#ifndef BOMB_NUM_MAX_PER_PLAYER  
  #define BOMB_NUM_MAX_PER_PLAYER 4
#endif

#ifndef BOMB_STRUCT
#define BOMB_STRUCT

typedef enum _BombState {
   AVAILABLE_BOMB,
   READY_BOMB,
   EXPLODING_BOMB,
   EXPLOITED_BOMB
} BombState;

typedef struct _Bomb {
   u8 id; 
   Position logicPosition;
   Position pixelPosition;
   BombState state;
   u8 timeToExplode;
   u8 timeLeft;
} Bomb;

#endif

bool Bomb_isAvailable(Bomb *bomb);
void Bomb_copyPosition(Position *originPosition, Position *targetPosition);
bool Bomb_isExploding(Bomb *bomb);

bool Bomb_isReadyForExplosion(Bomb *bomb);

bool Bomb_isExploited(Bomb *bomb);

void Bomb_setAsReady(Bomb *bomb);

void Bomb_setExploding(Bomb *bomb);
void Bomb_setAsAvailable(Bomb *bomb);
void Bomb_setAsExploited(Bomb *bomb);