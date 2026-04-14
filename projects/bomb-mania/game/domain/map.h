#include "msxgl.h"

#include "IndestructibleBlock.h"
#include "DestructibleBlock.h"  
#include "Player.h"
#include "Direction.h"
#include "CellInfo.h"

typedef struct MapStruct {
    u8 rows;
    u8 cols;
    IndestructibleBlock* indestructibleBlocks;
    DestructibleBlock* destructibleBlocks;
    Player *player;
} _Map;

extern _Map map;

void Map_set(_Map *map, u8 rows, u8 cols, Player *player);

bool Map_canMove(Player* player, Direction direction);

void Map_move(Player* player, Direction direction);

void Map_addBomb(Player* player);

void Map_canSetBomb(Player* player);

bool Map_isDead(Player* player);

void Blow();

CellInfo* Map_getBusyCells();

void Map_explodeActiveBombs();