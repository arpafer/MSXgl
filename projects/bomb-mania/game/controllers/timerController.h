#pragma once

#include "msxgl.h"

#ifndef GAME_COUNTDOWN_SECONDS
   #define GAME_COUNTDOWN_SECONDS 3
#endif

#ifndef TIMER_ID_ROUND_START
  #define TIMER_ID_ROUND_START 1 
#endif

#ifndef TIMER_ID_STAGE_COUNTDOWN         
  #define TIMER_ID_STAGE_COUNTDOWN 2        
#endif

bool TimerController_countSeconds(u8 countId, u8 seconds);
u8 TimerController_getRemainingSeconds(u8 timerId, u8 seconds);

void TimerController_createCount(u8 countId);
void TimerController_tick(void);

void TimerController_initialize(void);
void TimerController_removeTimerByTimerId(u8 timerId);
