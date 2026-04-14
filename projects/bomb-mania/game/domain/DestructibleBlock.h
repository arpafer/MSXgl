#include "msxgl.h"

#include "Position.h"

typedef struct DestructibleBlockStruct
{
    u8 id;
    Position position;    
    bool destroyed;
} DestructibleBlock;

bool DestructibleBlock_isDestroyed(DestructibleBlock* block);

void DestructibleBlock_setPosition(DestructibleBlock* block, Position position);

Position DestructibleBlock_getPosition(DestructibleBlock* block);
