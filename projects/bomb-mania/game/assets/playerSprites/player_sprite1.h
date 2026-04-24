#ifndef PLAYER_SPRITE1_H
#define PLAYER_SPRITE1_H

#include "msxgl.h"

// -----------------------------------------------------------------------------
// Player 1 - MSX1 sprite 16x16, 1 color
// -----------------------------------------------------------------------------
//
// Diseño:
// - Personaje pequeño tipo Bomb-manía / Bomberman.
// - Casco redondeado.
// - Silueta compacta y reconocible.
// - El frame quieto sirve como base visual del resto.
// - 1 solo color hardware.
//
// Cada frame 16x16 ocupa 4 patrones de 8x8:
//
//   patrón 0: superior izquierdo
//   patrón 1: inferior izquierdo
//   patrón 2: superior derecho
//   patrón 3: inferior derecho
//
// En modo sprite 16x16, el índice del patrón debe ser múltiplo de 4.
// -----------------------------------------------------------------------------

#define PLAYER1_SPRITE_PATTERN_INDEX      0

#define PLAYER1_PATTERNS_PER_FRAME        4
#define PLAYER1_FRAME_COUNT               9
#define PLAYER1_SPRITE_PATTERN_COUNT      \
    (PLAYER1_FRAME_COUNT * PLAYER1_PATTERNS_PER_FRAME)

typedef enum
{
    PLAYER1_FRAME_IDLE = 0,

    PLAYER1_FRAME_DOWN_0,
    PLAYER1_FRAME_DOWN_1,

    PLAYER1_FRAME_UP_0,
    PLAYER1_FRAME_UP_1,

    PLAYER1_FRAME_LEFT_0,
    PLAYER1_FRAME_LEFT_1,

    PLAYER1_FRAME_RIGHT_0,
    PLAYER1_FRAME_RIGHT_1

} Player1Frame;

#define PLAYER1_GET_PATTERN(frame) \
    ((u8)(PLAYER1_SPRITE_PATTERN_INDEX + ((u8)(frame) * PLAYER1_PATTERNS_PER_FRAME)))

static const u8 g_Player1WalkDownFrames[] =
{
    PLAYER1_FRAME_DOWN_0,
    PLAYER1_FRAME_DOWN_1
};

static const u8 g_Player1WalkUpFrames[] =
{
    PLAYER1_FRAME_UP_0,
    PLAYER1_FRAME_UP_1
};

static const u8 g_Player1WalkLeftFrames[] =
{
    PLAYER1_FRAME_LEFT_0,
    PLAYER1_FRAME_LEFT_1
};

static const u8 g_Player1WalkRightFrames[] =
{
    PLAYER1_FRAME_RIGHT_0,
    PLAYER1_FRAME_RIGHT_1
};

static const u8 g_Player1SpritePatterns[] =
{
    // -------------------------------------------------------------------------
    // Frame 0: IDLE / frontal quieto - versión compacta
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x03, 0x07, 0x0F, 0x1F, 0x1B, 0x1F, 0x0F, 0x07,

    // Inferior izquierdo
    0x0F, 0x1F, 0x3B, 0x33, 0x03, 0x07, 0x0C, 0x18,

    // Superior derecho
    0x00, 0x80, 0xC0, 0xE0, 0x60, 0xE0, 0xC0, 0x80,

    // Inferior derecho
    0xC0, 0xE0, 0x70, 0x30, 0x00, 0x80, 0xC0, 0x60,


    // -------------------------------------------------------------------------
    // Frame 1: DOWN_0 / andando hacia abajo
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x03, 0x07, 0x0F, 0x1F, 0x1B, 0x1F, 0x0F, 0x07,

    // Inferior izquierdo
    0x0F, 0x1F, 0x3B, 0x33, 0x03, 0x07, 0x0E, 0x18,

    // Superior derecho
    0x00, 0x80, 0xC0, 0xE0, 0x60, 0xE0, 0xC0, 0x80,

    // Inferior derecho
    0xC0, 0xE0, 0x70, 0x30, 0x00, 0x80, 0x30, 0x18,


    // -------------------------------------------------------------------------
    // Frame 2: DOWN_1 / andando hacia abajo
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x03, 0x07, 0x0F, 0x1F, 0x1B, 0x1F, 0x0F, 0x07,

    // Inferior izquierdo
    0x0F, 0x1F, 0x3B, 0x33, 0x03, 0x06, 0x0C, 0x18,

    // Superior derecho
    0x00, 0x80, 0xC0, 0xE0, 0x60, 0xE0, 0xC0, 0x80,

    // Inferior derecho
    0xC0, 0xE0, 0x70, 0x30, 0x00, 0xC0, 0x60, 0x30,


    // -------------------------------------------------------------------------
    // Frame 3: UP_0 / andando hacia arriba
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07,

    // Inferior izquierdo
    0x0F, 0x1F, 0x3F, 0x33, 0x03, 0x07, 0x0E, 0x18,

    // Superior derecho
    0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80,

    // Inferior derecho
    0xC0, 0xE0, 0xF0, 0x30, 0x00, 0x80, 0x30, 0x18,


    // -------------------------------------------------------------------------
    // Frame 4: UP_1 / andando hacia arriba
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07,

    // Inferior izquierdo
    0x0F, 0x1F, 0x3F, 0x33, 0x03, 0x06, 0x0C, 0x18,

    // Superior derecho
    0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80,

    // Inferior derecho
    0xC0, 0xE0, 0xF0, 0x30, 0x00, 0xC0, 0x60, 0x30,


    // -------------------------------------------------------------------------
    // Frame 5: LEFT_0 / andando hacia la izquierda
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x3F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x07, 0x1F, 0x3F, 0x37, 0x27, 0x07, 0x0C, 0x18,

    // Superior derecho
    0x00, 0xE0, 0xF0, 0xE0, 0xC0, 0x80, 0x80, 0x00,

    // Inferior derecho
    0x80, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00,


    // -------------------------------------------------------------------------
    // Frame 6: LEFT_1 / andando hacia la izquierda
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x3F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x07, 0x1F, 0x3F, 0x37, 0x27, 0x07, 0x1C, 0x30,

    // Superior derecho
    0x00, 0xE0, 0xF0, 0xE0, 0xC0, 0x80, 0x80, 0x00,

    // Inferior derecho
    0x80, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00,


    // -------------------------------------------------------------------------
    // Frame 7: RIGHT_0 / andando hacia la derecha
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x07, 0x0F, 0x07, 0x03, 0x01, 0x01, 0x00,

    // Inferior izquierdo
    0x01, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,

    // Superior derecho
    0xC0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8,

    // Inferior derecho
    0xE0, 0xF8, 0xFC, 0xEC, 0xE4, 0xE0, 0x30, 0x18,


    // -------------------------------------------------------------------------
    // Frame 8: RIGHT_1 / andando hacia la derecha
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x07, 0x0F, 0x07, 0x03, 0x01, 0x01, 0x00,

    // Inferior izquierdo
    0x01, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,

    // Superior derecho
    0xC0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8,

    // Inferior derecho
    0xE0, 0xF8, 0xFC, 0xEC, 0xE4, 0xE0, 0x38, 0x0C
};

#endif