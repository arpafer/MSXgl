#include "msxgl.h"
#include "vdp.h"

#include "countDownView.h"
#include "../controllers/timerController.h"

// #include "font/font_mgl_sample6.h"

#ifndef ROUND_SCREEN1_WIDTH_CHR
  #define ROUND_SCREEN1_WIDTH_CHR 32
#endif

#ifndef  STAGE_COUNTDOWN_SECONDS
  #define STAGE_COUNTDOWN_SECONDS 180 
#endif

extern const unsigned char g_Font_MGL_Sample6[];

static u8 g_CountDown = STAGE_COUNTDOWN_SECONDS;

static void CountDown_printTime(void)
{
    Print_SetCharSize(1, 1);
    Print_SetTextFont(g_Font_MGL_Sample6, 1);
    Print_SetColor(COLOR_WHITE, COLOR_BLACK);
    Print_SetPosition((ROUND_SCREEN1_WIDTH_CHR - 8) / 2, 23);
    Print_DrawFormat("Time: %d", g_CountDown);
}

static void CountDown_printTimeDigits(void)
{
    Print_SetPosition(((ROUND_SCREEN1_WIDTH_CHR - 8) / 2) + 6, 23);
    Print_DrawChar('0' + (g_CountDown / 100));
    Print_DrawChar('0' + ((g_CountDown / 10) % 10));
    Print_DrawChar('0' + (g_CountDown % 10));
}

static void CountDown_updateTime(u8 seconds)
{
    u8 remainingSeconds;

    remainingSeconds = TimerController_getRemainingSeconds(
        TIMER_ID_STAGE_COUNTDOWN,
        seconds);

    if (remainingSeconds == g_CountDown)
        return;

    g_CountDown = remainingSeconds;
    CountDown_printTimeDigits();
}

void CountDown_render(u8 seconds)
{
    g_CountDown = seconds;
    CountDown_printTime();
    TimerController_initialize();
    TimerController_createCount(TIMER_ID_STAGE_COUNTDOWN);
}

bool CountDown_isEnded(u8 stageCountdownTime)
{
    bool ended;

    EnableInterrupt();
    Halt();
    TimerController_tick();

    CountDown_updateTime(stageCountdownTime);
    ended = TimerController_countSeconds(TIMER_ID_STAGE_COUNTDOWN, stageCountdownTime);

    if (ended)
        TimerController_removeTimerByTimerId(TIMER_ID_STAGE_COUNTDOWN);

    return ended;
}
