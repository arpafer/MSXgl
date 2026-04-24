#include "msxgl.h"
#include "playerController.h"

static Direction PlayerController_getArrowKeyboardDirection(void)
{
    if (Keyboard_IsKeyPressed(KEY_UP))
        return DIRECTION_UP;

    if (Keyboard_IsKeyPressed(KEY_RIGHT))
        return DIRECTION_RIGHT;

    if (Keyboard_IsKeyPressed(KEY_DOWN))
        return DIRECTION_DOWN;

    if (Keyboard_IsKeyPressed(KEY_LEFT))
        return DIRECTION_LEFT;

    return DIRECTION_NONE;
}

void PlayerController_init(u8 playerId) {
    
}

Direction PlayerController_manageMove(u8 playerId) {
   if (playerId == 1) {
      return PlayerController_getArrowKeyboardDirection;
   }
}