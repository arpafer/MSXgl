
#include "msxgl.h"

#include "Direction.h"
#include "map.h"
#include "CellInfo.h"
#include "Timer.h"
#include "Player.h"

typedef struct LevelStruct
{
    u8 numPlayers;    
    Map* map;
    Timer* timer;
    Player players[4];

} Level;

extern Level level;

void Level_setLevel(Map* map, u8 numPlayers, Player* players);

bool Level_canMove(u8 playerId, Direction direction);

void Level_move(u8 playerId, Direction direction);

void Level_addBomb(u8 playerId);

bool Level_canSetBomb(u8 playerId);

bool Level_isDead(u8 playerId);   

CellInfo* Level_getBusyCells();

void Level_explodeActiveBombs();