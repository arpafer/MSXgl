#include "msxgl.h"
#include "vdp.h"
#include "round.h"

#include "../assets/rounds/round_title_tiles.h"
#include "../assets/rounds/round_number_tiles.h"
#include "../assets/rounds/round_gradient_font_tiles.h"

#include "../controllers/timerController.h"

#ifndef ROUND_SCREEN1_WIDTH_CHR
#define ROUND_SCREEN1_WIDTH_CHR 32
#endif

#ifndef ROUND_SCREEN1_HEIGHT_CHR
#define ROUND_SCREEN1_HEIGHT_CHR 24
#endif

#define ROUND_TILE_BASE_OFFSET       160
#define ROUND_TILE_TITLE_OFFSET      ROUND_TILE_BASE_OFFSET
#define ROUND_TILE_NUMBER_OFFSET     (ROUND_TILE_TITLE_OFFSET + ROUND_TITLE_TOTAL_TILE_COUNT)
#define ROUND_TILE_GRADIENT_OFFSET   (ROUND_TILE_NUMBER_OFFSET + ROUND_NUMBER_TOTAL_TILE_COUNT)
#define ROUND_TITLE_START_X          7
#define ROUND_TITLE_START_Y          9
#define ROUND_SUBTITLE_START_X       11
#define ROUND_SUBTITLE_START_Y       14

void Render_init()
{
    VDP_Initialize();
    VDP_SetMode(VDP_MODE_SCREEN2);
    VDP_SetColor(COLOR_BLACK);
    Print_Initialize();
    VDP_EnableVBlank(TRUE);
    VDP_ClearVRAM();
}

static void Round_loadTileSetToAllBanks(const u8* patterns, const u8* colors, u8 tileCount, u8 offset)
{
    VDP_LoadBankPattern_GM2(patterns, tileCount, 0, offset);
    VDP_LoadBankPattern_GM2(patterns, tileCount, 1, offset);
    VDP_LoadBankPattern_GM2(patterns, tileCount, 2, offset);

    VDP_LoadBankColor_GM2(colors, tileCount, 0, offset);
    VDP_LoadBankColor_GM2(colors, tileCount, 1, offset);
    VDP_LoadBankColor_GM2(colors, tileCount, 2, offset);
}

static void Round_renderGlyph2x2(u8 x, u8 y, u8 tileBase)
{
    VDP_Poke_GM2(x,     y,     tileBase + 0);
    VDP_Poke_GM2(x + 1, y,     tileBase + 1);
    VDP_Poke_GM2(x,     y + 1, tileBase + 2);
    VDP_Poke_GM2(x + 1, y + 1, tileBase + 3);
}

static void Round_renderGlyph1x2(u8 x, u8 y, u8 tileTop, u8 tileBottom)
{
    VDP_Poke_GM2(x, y, tileTop);
    VDP_Poke_GM2(x, y + 1, tileBottom);
}

static void Round_renderTitle(u8 levelId)
{
    u8 x = ROUND_TITLE_START_X;

    Round_renderGlyph2x2(x, ROUND_TITLE_START_Y, ROUND_TILE_TITLE_OFFSET + ROUND_TITLE_TILE_BASE(ROUND_TITLE_GLYPH_R)); x += 2;
    Round_renderGlyph2x2(x, ROUND_TITLE_START_Y, ROUND_TILE_TITLE_OFFSET + ROUND_TITLE_TILE_BASE(ROUND_TITLE_GLYPH_O)); x += 2;
    Round_renderGlyph2x2(x, ROUND_TITLE_START_Y, ROUND_TILE_TITLE_OFFSET + ROUND_TITLE_TILE_BASE(ROUND_TITLE_GLYPH_U)); x += 2;
    Round_renderGlyph2x2(x, ROUND_TITLE_START_Y, ROUND_TILE_TITLE_OFFSET + ROUND_TITLE_TILE_BASE(ROUND_TITLE_GLYPH_N)); x += 2;
    Round_renderGlyph2x2(x, ROUND_TITLE_START_Y, ROUND_TILE_TITLE_OFFSET + ROUND_TITLE_TILE_BASE(ROUND_TITLE_GLYPH_D)); x += 2;
    Round_renderGlyph1x2(x,
                         ROUND_TITLE_START_Y,
                         ROUND_TILE_TITLE_OFFSET + ROUND_TITLE_TILE_TL(ROUND_TITLE_GLYPH_COLON),
                         ROUND_TILE_TITLE_OFFSET + ROUND_TITLE_TILE_BL(ROUND_TITLE_GLYPH_COLON));
    x += 2;

    Round_renderGlyph2x2(x, ROUND_TITLE_START_Y, ROUND_TILE_NUMBER_OFFSET + ROUND_NUMBER_TILE_BASE(ROUND_NUMBER_GLYPH_0)); x += 2;
    Round_renderGlyph2x2(x, ROUND_TITLE_START_Y, ROUND_TILE_NUMBER_OFFSET + ROUND_NUMBER_TILE_BASE(ROUND_NUMBER_GLYPH_0)); x += 2;
    Round_renderGlyph2x2(x, ROUND_TITLE_START_Y, ROUND_TILE_NUMBER_OFFSET + ROUND_NUMBER_TILE_BASE(ROUND_NUMBER_GLYPH_INDEX(levelId)));
}

static void Round_renderSubtitle(const char* subtitle)
{
    u8 x = ROUND_SUBTITLE_START_X;

    while (*subtitle != '\0')
    {
        u8 tileIndex = ROUND_SUBTITLE_TILE_INDEX(*subtitle);
        if (tileIndex != 0xFF)
            VDP_Poke_GM2(x, ROUND_SUBTITLE_START_Y, ROUND_TILE_GRADIENT_OFFSET + tileIndex);
        x++;
        subtitle++;
    }
}

void Round_loadTiles()
{
    Round_loadTileSetToAllBanks(g_RoundTitleTilePatterns,
                                g_RoundTitleTileColors,
                                ROUND_TITLE_TOTAL_TILE_COUNT,
                                ROUND_TILE_TITLE_OFFSET);

    Round_loadTileSetToAllBanks(g_RoundNumberTilePatterns,
                                g_RoundNumberTileColors,
                                ROUND_NUMBER_TOTAL_TILE_COUNT,
                                ROUND_TILE_NUMBER_OFFSET);

    Round_loadTileSetToAllBanks(g_RoundGradientTilePatterns,
                                g_RoundGradientTileColors,
                                ROUND_SUBTITLE_GLYPH_COUNT,
                                ROUND_TILE_GRADIENT_OFFSET);
}

void Round_render(u8 levelId)
{
    Render_init();
    Round_loadTiles();
    Round_renderTitle(levelId);
    Round_renderSubtitle("\"JUST FUN!\"");

    TimerController_resetCount();    

    /*
    Print_SetCharSize(3, 3);
    Print_SetTextFont(g_Font_MGL_Sample8, 1);
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);
    highMiddle = ROUND_SCREEN1_HEIGHT_CHR / 2;
    Print_SetPosition(10, highMiddle - 2);
    Print_DrawFormat("Round: %03d", levelId);
    Print_SetPosition(10, highMiddle);
    Print_DrawFormat("JUST FUN!");
    */
}

bool Round_isRoundEnded()
{    
    return TimerController_countSeconds(GAME_COUNTDOWN);
}
