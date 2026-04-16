// ____________________________
// ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │   ▄▄▄                ▄▄      
// ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │  ▀█▄  ▄▀██ ▄█▄█ ██▀▄ ██  ▄███
// █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │  ▄▄█▀ ▀▄██ ██ █ ██▀  ▀█▄ ▀█▄▄
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘                 ▀▀
//  Program template
//─────────────────────────────────────────────────────────────────────────────

//=============================================================================
// INCLUDES
//=============================================================================
#include "msxgl.h"
#include "game/views/menu.h"
#include "game/views/level.h"
#include "game/views/round.h"

//=============================================================================
// DEFINES
//=============================================================================

// Library's logo
// #define MSX_GL "\x01\x02\x03\x04\x05\x06"

//=============================================================================
// READ-ONLY DATA
//=============================================================================

// Fonts data
// #include "font/font_mgl_sample6.h"

// Animation characters
const u8 g_ChrAnim[] = { '-', '/', '|', '\\' };

//=============================================================================
// MAIN LOOP
//=============================================================================

//-----------------------------------------------------------------------------
/// Program entry point
void main()
{
/*	VDP_Initialize();
	VDP_SetMode(VDP_MODE_SCREEN1);
	VDP_EnableVBlank(TRUE);
	VDP_ClearVRAM();  */

	/*Print_SetTextFont(g_Font_MGL_Sample6, 1);
	Print_SetColor(COLOR_WHITE, COLOR_BLACK);
	Print_SetPosition(0, 0);
	Print_DrawText(" Clone MSX Bomb Mania");	 */

	Menu_render();
/*	u8 count = 0;	
	while (!Keyboard_IsKeyPressed(KEY_SPACE))
	{
		Print_SetPosition(39, 0);
		// Print_DrawChar(g_ChrAnim[count++ % 4]);
		Halt();
	}	 */
    unsigned char option = Menu_getSelectedOption();	
	bool exit = FALSE;
	u8 levelId = 1;
	while (!exit) {
	   Round_render(levelId);
	   while (!Round_isRoundEnded());

       Level_render(levelId);
	   exit = TRUE;
	}
	exit = FALSE;
	while (!exit); 
	Bios_Exit(0);

}