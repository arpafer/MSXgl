#include "msxgl.h"
#include "vdp.h"
#include "menu.h"

#define MSX_GL "\x01\x02\x03\x04\x05\x06"
#include "font/font_mgl_sample6.h"

void Menu_init() {
    VDP_Initialize();
	VDP_SetMode(VDP_MODE_SCREEN1);
    Print_Initialize();
	VDP_EnableVBlank(TRUE);
	VDP_ClearVRAM();
}



void Menu_render() {
   Menu_init();
   Print_SetCharSize(1, 1);
   Print_SetTextFont(g_Font_MGL_Sample6, 1);
   Print_SetColor(COLOR_WHITE, COLOR_BLACK);
   Print_SetPosition(0, 0);  
   Print_DrawText("Selecciona numero de jugadores. ");
   Print_SetPosition(0, 3);
   Print_DrawText("1. Dos jugadores");
   Print_SetPosition(0, 5);
   Print_DrawText("2. Tres jugadores");
   Print_SetPosition(0, 7);
   Print_DrawText("3. Cuatro jugadores");

}

unsigned char Menu_getSelectedOption() {
    while (!Keyboard_IsKeyPressed(KEY_1) && !Keyboard_IsKeyPressed(KEY_2) && !Keyboard_IsKeyPressed(KEY_3))
	{		
		Halt();
	}
    if (Keyboard_IsKeyPressed(KEY_1)) {
        Print_SetPosition(0, 9);
        Print_DrawText("Se ha seleccionado 2 jugadores");
        return 1;
    }
    if (Keyboard_IsKeyPressed(KEY_2)) {
        Print_SetPosition(0, 9);
        Print_DrawText("Se ha seleecionado 3 jugadores");
        return 2;
    }
    if (Keyboard_IsKeyPressed(KEY_3)) {
        Print_SetPosition(0, 9);
        Print_DrawText("Se ha seleecionado 4 jugadores");
        return 3;
    }
}
