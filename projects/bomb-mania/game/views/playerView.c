#include "msxgl.h"
#include "playerView.h"
#include "vdp.h"
#include "../assets/playerSprites/player_sprite1.h"
#include "../assets/playerSprites/player_sprite2.h"
#include "../assets/playerSprites/player_sprite3.h"
#include "../assets/playerSprites/player_sprite4.h"
#include "../controllers/playerController.h"
#include "../controllers/levelController.h"
#include "../domain/Direction.h"
#include "../domain/Bomb.h"
#include "BombView.h"

#ifndef LEVEL_LOGICAL_COLS
#define LEVEL_LOGICAL_COLS 16
#endif

#ifndef LEVEL_LOGICAL_ROWS
#define LEVEL_LOGICAL_ROWS 10
#endif

u16 Player_getPixelFromColumn(u8 column)
{
    return column * 16;
}

u8 Player_getPixelFromRow(u8 row)
{
    return row * 16;
}

u8 Player_getStartColumn(u8 playerId)
{
    if (playerId == 1)
    {
        return 1;
    }
    if (playerId == 2)
    {
        return LEVEL_LOGICAL_COLS - 2;
    }
    if (playerId == 3)
    {
        return LEVEL_LOGICAL_COLS - 2;
    }
    if (playerId == 4)
    {
        return 1;
    }
    return 1;
}

u8 Player_getStartRow(u8 playerId)
{
    if (playerId == 1)
    {
        return 1;
    }
    if (playerId == 2)
    {
        return LEVEL_LOGICAL_ROWS - 2;
    }
    if (playerId == 3)
    {
        return 1;
    }
    if (playerId == 4)
    {
        return LEVEL_LOGICAL_ROWS - 2;
    }
    return 1;
}

const u8 *Player_getSpritePatterns(u8 playerId)
{
    if (playerId == 1)
        return g_Player1SpritePatterns;

    if (playerId == 2)
        return g_Player2SpritePatterns;

    if (playerId == 3)
        return g_Player3SpritePatterns;

    if (playerId == 4)
        return g_Player4SpritePatterns;

    return 0;
}

u8 Player_getPatternIndex(u8 playerId)
{
    if (playerId == 1)
        return PLAYER1_SPRITE_PATTERN_INDEX;

    if (playerId == 2)
        return PLAYER2_SPRITE_PATTERN_INDEX;

    if (playerId == 3)
        return PLAYER3_SPRITE_PATTERN_INDEX;

    if (playerId == 4)
        return PLAYER4_SPRITE_PATTERN_INDEX;

    return 0;
}
u8 Player_getPatternCount(u8 playerId)
{
    if (playerId == 1)
        return PLAYER1_SPRITE_PATTERN_COUNT;

    if (playerId == 2)
        return PLAYER2_SPRITE_PATTERN_COUNT;

    if (playerId == 3)
        return PLAYER3_SPRITE_PATTERN_COUNT;

    if (playerId == 4)
        return PLAYER4_SPRITE_PATTERN_COUNT;

    return 0;
}

u8 Player_getFrameIdle(u8 playerId)
{
    if (playerId == 1)
        return PLAYER1_FRAME_IDLE;

    if (playerId == 2)
        return PLAYER2_FRAME_IDLE;

    if (playerId == 3)
        return PLAYER3_FRAME_IDLE;

    if (playerId == 4)
        return PLAYER4_FRAME_IDLE;

    return PLAYER1_FRAME_IDLE;
}

static u8 Player_getFrameDown(u8 playerId, u8 walkFrame)
{
    if (playerId == 1)
    {
        return walkFrame ? PLAYER1_FRAME_DOWN_1 : PLAYER1_FRAME_DOWN_0;
    }
    else if (playerId == 2)
    {
        return walkFrame ? PLAYER2_FRAME_DOWN_1 : PLAYER2_FRAME_DOWN_0;
    }
    else if (playerId == 3)
    {
        return walkFrame ? PLAYER3_FRAME_DOWN_1 : PLAYER3_FRAME_DOWN_0;
    }
    else if (playerId == 4)
    {
        return walkFrame ? PLAYER4_FRAME_DOWN_1 : PLAYER4_FRAME_DOWN_0;
    }
}

static u8 Player_getFrameUp(u8 playerId, u8 walkFrame)
{
    if (playerId == 1)
    {
        return walkFrame ? PLAYER1_FRAME_UP_1 : PLAYER1_FRAME_UP_0;
    }
    else if (playerId == 2)
    {
        return walkFrame ? PLAYER2_FRAME_UP_1 : PLAYER2_FRAME_UP_0;
    }
    else if (playerId == 3)
    {
        return walkFrame ? PLAYER3_FRAME_UP_1 : PLAYER3_FRAME_UP_0;
    }
    else if (playerId == 4)
    {
        return walkFrame ? PLAYER4_FRAME_UP_1 : PLAYER4_FRAME_UP_0;
    }
}

static u8 Player_getFrameRight(u8 playerId, u8 walkFrame)
{
    if (playerId == 1)
    {
        return walkFrame ? PLAYER1_FRAME_RIGHT_1 : PLAYER1_FRAME_RIGHT_0;
    }
    else if (playerId == 2)
    {
        return walkFrame ? PLAYER2_FRAME_RIGHT_1 : PLAYER2_FRAME_RIGHT_0;
    }
    else if (playerId == 3)
    {
        return walkFrame ? PLAYER3_FRAME_RIGHT_1 : PLAYER3_FRAME_RIGHT_0;
    }
    else if (playerId == 4)
    {
        return walkFrame ? PLAYER4_FRAME_RIGHT_1 : PLAYER4_FRAME_RIGHT_0;
    }
}

static u8 Player_getFrameLeft(u8 playerId, u8 walkFrame)
{
    if (playerId == 1)
    {
        return walkFrame ? PLAYER1_FRAME_LEFT_1 : PLAYER1_FRAME_LEFT_0;
    }
    else if (playerId == 2)
    {
        return walkFrame ? PLAYER2_FRAME_LEFT_1 : PLAYER2_FRAME_LEFT_0;
    }
    else if (playerId == 3)
    {
        return walkFrame ? PLAYER3_FRAME_LEFT_1 : PLAYER3_FRAME_LEFT_0;
    }
    else if (playerId == 4)
    {
        return walkFrame ? PLAYER4_FRAME_LEFT_1 : PLAYER4_FRAME_LEFT_0;
    }
}

u8 Player_getColor(u8 playerId)
{
    if (playerId == 1)
    {
        return COLOR_DARK_BLUE;
    }
    if (playerId == 2)
    {
        return COLOR_MAGENTA;
    }
    if (playerId == 3)
    {
        return COLOR_DARK_RED;
    }
    if (playerId == 4)
    {
        return COLOR_BLACK;
    }
    return COLOR_DARK_BLUE;
}

#define PLAYER_PATTERNS_PER_FRAME 4

u8 Player_getFramePattern(u8 playerId, u8 frame)
{
    return Player_getPatternIndex(playerId) + (frame * PLAYER_PATTERNS_PER_FRAME);
}

u8 Player_getBasePattern(u8 playerId)
{
    return Player_getFramePattern(playerId, Player_getFrameIdle(playerId));
}

static void Player_draw(u8 playerId, Player *player, u8 frame)
{
    VDP_SetSpriteSM1(
        playerId - 1,
        player->pixelPosition->x,
        player->pixelPosition->y,
        Player_getFramePattern(playerId, frame),
        Player_getColor(playerId));
}

void Player_render(u8 playerId)
{
    Player *player = PlayerController_init(playerId);

    const u8 *patterns = Player_getSpritePatterns(playerId);
    if (patterns == 0)
        return;

    VDP_SetSpriteFlag(VDP_SPRITE_SIZE_16 | VDP_SPRITE_SCALE_1);
    VDP_LoadSpritePattern(
        patterns,
        Player_getPatternIndex(playerId),
        Player_getPatternCount(playerId));

    Player_draw(playerId, player, Player_getFrameIdle(playerId));
}

static u8 Player_getWalkFrame(u8 playerId, Direction direction)
{
    static u8 animationTick = 0;
    u8 walkFrame = (animationTick >> 3) & 1;

    animationTick++;

    if (direction == DIRECTION_NONE)
        return Player_getFrameIdle(playerId);

    if (direction == DIRECTION_DOWN)
        return Player_getFrameDown(playerId, walkFrame);

    if (direction == DIRECTION_UP)
        return Player_getFrameUp(playerId, walkFrame);

    if (direction == DIRECTION_LEFT)
        return Player_getFrameLeft(playerId, walkFrame);

    if (direction == DIRECTION_RIGHT)
        return Player_getFrameRight(playerId, walkFrame);

    return Player_getFrameIdle(playerId);
}

void Player_manageMove(u8 playerId, u8 *logicMap)
{
    Player *player = 0;
    Direction direction = PlayerController_manageMove(playerId, &player, logicMap);

    if (player != 0)
        Player_draw(playerId, player, Player_getWalkFrame(playerId, direction));
}

bool Player_hasShot(u8 playerId)
{
    Player *player = 0;
    bool hasShot = PlayerController_hasShot(playerId, &player);
    return hasShot;
}

void PlayerView_renderBomb(Bomb *bomb, u8 playerId)
{
    Player *player = PlayerController_getPlayerWithId(playerId);
    if (Player_canPlaceBomb(player))
    {
        Player_setBombPlaced(player, bomb->id);
        Bomb_copyPosition(player->logicPosition, &(bomb->logicPosition));
        Bomb_copyPosition(player->pixelPosition, &(bomb->pixelPosition));
        BombView_render(bomb);
    }
}

void PlayerView_updateBombsStateOfPlayer(u8 playerId) {
    Player *player = PlayerController_getPlayerWithId(playerId);
    for (int i = 0; i < player->bombCount; i++) {
        u8 bombId = player->BombIds[i];
        Bomb *bomb = LevelController_getBombById(bombId);
        if (bomb != 0) {
            if (Bomb_isExploding(bomb)) {
               BombView_renderExplosion(bomb, 1);                              
            }
        }
     }
}
