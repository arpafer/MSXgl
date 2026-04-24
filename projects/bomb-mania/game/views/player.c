#include "msxgl.h"
#include "player.h"
#include "vdp.h"
#include "../assets/playerSprites/player_sprite1.h"
#include "../assets/playerSprites/player_sprite2.h"
#include "../assets/playerSprites/player_sprite3.h"
#include "../assets/playerSprites/player_sprite4.h"

#define LEVEL_LOGICAL_COLS 16
#define LEVEL_LOGICAL_ROWS 10

u16 Player_getPixelFromColumn(u8 column) {
   return column * 16;
}

u8 Player_getPixelFromRow(u8 row) {
    return row * 16;
}

u8 Player_getStartColumn(u8 playerId) {
    if (playerId == 1) {
        return 1;
    }
    if (playerId == 2) {
        return LEVEL_LOGICAL_COLS - 2;
    }
    if (playerId == 3) {
        return LEVEL_LOGICAL_COLS - 2; 
    }
    if (playerId == 4) {
        return 1;
    }
    return 1;
}

u8 Player_getStartRow(u8 playerId) {
    if (playerId == 1) {
        return 1;
    }
    if (playerId == 2) {
        return LEVEL_LOGICAL_ROWS - 2;
    }
    if (playerId == 3) {
        return 1; 
    }
    if (playerId == 4) {
        return LEVEL_LOGICAL_ROWS - 2;
    }
    return 1;
}

const u8* Player_getSpritePatterns(u8 playerId)
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

u8 Player_getColor(u8 playerId) {
    if (playerId == 1) {
        return COLOR_DARK_BLUE;
    }
    if (playerId == 2) {
        return COLOR_MAGENTA;
    }
    if (playerId == 3) {
        return COLOR_DARK_RED;
    }
    if (playerId == 4) {
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

void Player_render(u8 playerId)
{
    const u8* patterns = Player_getSpritePatterns(playerId);
    if (patterns == 0)
        return;

    VDP_SetSpriteFlag(VDP_SPRITE_SIZE_16 | VDP_SPRITE_SCALE_1);
    VDP_LoadSpritePattern(
        patterns,
        Player_getPatternIndex(playerId),
        Player_getPatternCount(playerId));

    VDP_SetSpriteSM1(
        playerId - 1,
        Player_getPixelFromColumn(Player_getStartColumn(playerId)),
        Player_getPixelFromRow(Player_getStartRow(playerId)),
        Player_getBasePattern(playerId),
        Player_getColor(playerId));
}

void Player_manageMove(u8 playerId)
{
}