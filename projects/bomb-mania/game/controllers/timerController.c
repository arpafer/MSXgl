#include "msxgl.h"

static bool g_TimerActive = FALSE;
static bool g_TimerCompleted = FALSE;
static u16 g_StartJiffy = 0;
static u16 g_TargetJiffies = 0;

void TimerController_resetCount(void)
{
    g_TimerActive = FALSE;
    g_TimerCompleted = FALSE;
    g_StartJiffy = 0;
    g_TargetJiffies = 0;
}

bool TimerController_countSeconds(u8 seconds)
{
    u16 requestedJiffies;
    u16 elapsedJiffies;
    u8 ticksPerSecond;

    if (seconds == 0)
        return TRUE;

    ticksPerSecond = Sys_Is60Hz() ? 60 : 50;
    requestedJiffies = (u16)seconds * ticksPerSecond;

    if (g_TimerCompleted && (g_TargetJiffies == requestedJiffies))
        return TRUE;

    if ((!g_TimerActive) || (g_TargetJiffies != requestedJiffies))
    {
        g_TimerActive = TRUE;
        g_TimerCompleted = FALSE;
        g_StartJiffy = g_JIFFY;
        g_TargetJiffies = requestedJiffies;
        return FALSE;
    }

    if (g_TimerCompleted)
        return TRUE;

    elapsedJiffies = g_JIFFY - g_StartJiffy;

    if (elapsedJiffies >= g_TargetJiffies)
    {
        g_TimerCompleted = TRUE;
        g_TimerActive = FALSE;
        return TRUE;
    }

    return FALSE;
}
