#include "msxgl.h"

#include "Position.h"

typedef struct IndestructibleBlockStruct
{
    u8 id;
    Position position;    
} IndestructibleBlock;

void IndestructibleBlock_setPosition(IndestructibleBlock* block, Position position);

Position IndestructibleBlock_getPosition(IndestructibleBlock* block);