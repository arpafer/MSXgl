#include "timerController.h"
#include "stdlib.h"
#include "../assets/rounds/round_gradient_font_tiles.h"

#define TIMER_DEBUG_TILE_GRADIENT_OFFSET 220

#define TIMER_POOL_SIZE 16

typedef struct _TimerDef
{
    bool Used;
    u8 timerId;
    bool TimerActive;
    bool TimerCompleted;
    u16 StartJiffy;
    u16 TargetJiffies;
} Timer;

static Timer g_Timers[TIMER_POOL_SIZE];
static u16 g_TimerTicks = 0;

static void TimerController_debugMark(u8 x, u8 y, char chr)
{
    u8 tileIndex = ROUND_SUBTITLE_TILE_INDEX(chr);

    if (tileIndex != 0xFF)
        VDP_Poke_GM2(x, y, TIMER_DEBUG_TILE_GRADIENT_OFFSET + tileIndex);
}

static void TimerController_debugTraceChar(u8* x, u8 y, char chr)
{
    if (*x < 32)
    {
        TimerController_debugMark(*x, y, chr);
        (*x)++;
    }
}

static void TimerController_clearTimer(Timer* timer)
{
    timer->Used = FALSE;
    timer->timerId = 0;
    timer->TimerActive = FALSE;
    timer->TimerCompleted = FALSE;
    timer->StartJiffy = 0;
    timer->TargetJiffies = 0;
}

static void TimerController_resetTimer(Timer* timer, u8 timerId)
{
    timer->Used = TRUE;
    timer->timerId = timerId;
    timer->TimerActive = FALSE;
    timer->TimerCompleted = FALSE;
    timer->StartJiffy = 0;
    timer->TargetJiffies = 0;
}

void TimerController_initialize(void)
{
    u8 i;

    for (i = 0; i < TIMER_POOL_SIZE; i++)
        TimerController_clearTimer(&g_Timers[i]);

    g_TimerTicks = 0;
}

static Timer* TimerController_searchTimerByTimerId(u8 timerId)
{
    u8 i;

    for (i = 0; i < TIMER_POOL_SIZE; i++)
    {
        if (!g_Timers[i].Used)
            continue;

        if (g_Timers[i].timerId == timerId)
            return &g_Timers[i];
    }

    return NULL;
}

static Timer* TimerController_insertNewTimer(u8 timerId)
{
    u8 i;

    for (i = 0; i < TIMER_POOL_SIZE; i++)
    {
        if (!g_Timers[i].Used)
        {
            TimerController_resetTimer(&g_Timers[i], timerId);
            return &g_Timers[i];
        }
    }

    return NULL;
}

void TimerController_removeTimerByTimerId(u8 timerId)
{
    Timer* timer = TimerController_searchTimerByTimerId(timerId);

    if (timer == NULL)
        return;

    TimerController_clearTimer(timer);
}

void TimerController_createCount(u8 timerId)
{
    Timer* timer;
    timer = TimerController_searchTimerByTimerId(timerId);

    if (timer == NULL)
    {
        timer = TimerController_insertNewTimer(timerId);

        if (timer == NULL)
            return;
    }

    TimerController_resetTimer(timer, timerId);
}

void TimerController_tick(void)
{
    g_TimerTicks++;
}

static Timer* TimerController_requireTimer(u8 timerId)
{
    Timer* timer = TimerController_searchTimerByTimerId(timerId);

    if (timer != NULL)
        return timer;

    TimerController_createCount(timerId);
    return TimerController_searchTimerByTimerId(timerId);
}

static u16 TimerController_getRequestedJiffies(u8 seconds)
{
    u8 ticksPerSecond = Sys_Is60Hz() ? 60 : 50;

    return (u16)seconds * ticksPerSecond;
}

static bool TimerController_updateRequestedTime(Timer* timer, u8 seconds, u16 currentJiffy)
{
    u16 requestedJiffies = TimerController_getRequestedJiffies(seconds);

    if (timer->TimerCompleted && (timer->TargetJiffies == requestedJiffies))
        return TRUE;

    if (timer->TimerActive && (timer->TargetJiffies == requestedJiffies))
        return FALSE;

    timer->TimerActive = TRUE;
    timer->TimerCompleted = FALSE;
    timer->StartJiffy = currentJiffy;
    timer->TargetJiffies = requestedJiffies;
    return FALSE;
}

static bool TimerController_hasCompletedTime(Timer* timer, u16 currentJiffy)
{
    u16 elapsedJiffies;

    if (timer->TimerCompleted)
        return TRUE;

    elapsedJiffies = currentJiffy - timer->StartJiffy;

    if (elapsedJiffies < timer->TargetJiffies)
        return FALSE;

    timer->TimerCompleted = TRUE;
    timer->TimerActive = FALSE;
    return TRUE;
}

static u16 TimerController_getElapsedJiffies(Timer* timer, u16 currentJiffy)
{
    u16 elapsedJiffies = currentJiffy - timer->StartJiffy;

    if (elapsedJiffies < timer->TargetJiffies)
        return elapsedJiffies;

    return timer->TargetJiffies;
}

static u8 TimerController_convertJiffiesToRemainingSeconds(u8 seconds, u16 elapsedJiffies)
{
    u16 elapsedSeconds = elapsedJiffies / TimerController_getRequestedJiffies(1);

    if (elapsedSeconds >= seconds)
        return 0;

    return seconds - (u8)elapsedSeconds;
}

bool TimerController_countSeconds(u8 timerId, u8 seconds)
{
    Timer* timer;
    u16 currentJiffy;

    if (seconds == 0)
        return TRUE;

    currentJiffy = g_TimerTicks;
    timer = TimerController_requireTimer(timerId);

    if (timer == NULL)
        return FALSE;

    if (TimerController_updateRequestedTime(timer, seconds, currentJiffy))
        return TRUE;

    return TimerController_hasCompletedTime(timer, currentJiffy);
}

u8 TimerController_getRemainingSeconds(u8 timerId, u8 seconds)
{
    Timer* timer;
    u16 currentJiffy;

    if (seconds == 0)
        return 0;

    currentJiffy = g_TimerTicks;
    timer = TimerController_requireTimer(timerId);

    if (timer == NULL)
        return seconds;

    TimerController_updateRequestedTime(timer, seconds, currentJiffy);
    return TimerController_convertJiffiesToRemainingSeconds(
        seconds,
        TimerController_getElapsedJiffies(timer, currentJiffy));
}
