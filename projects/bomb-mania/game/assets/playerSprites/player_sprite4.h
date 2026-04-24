#ifndef PLAYER_SPRITE4_H
#define PLAYER_SPRITE4_H

#include "msxgl.h"

// -----------------------------------------------------------------------------
// Player 4 - MSX1 sprite 16x16, 1 color
// -----------------------------------------------------------------------------
//
// Silueta:
// - Más ancho que los demás personajes
// - Hombros grandes
// - Casco/cabeza con dos pequeños salientes superiores
// - Cuerpo más pesado
//
// Índice base:
// - Player 1 usa 0..35
// - Player 2 usa 36..71
// - Player 3 usa 72..107
// - Player 4 usa 108..143
//
// Cada frame 16x16 ocupa 4 patrones de 8x8:
//
//   1) superior izquierdo
//   2) inferior izquierdo
//   3) superior derecho
//   4) inferior derecho
//
// -----------------------------------------------------------------------------

#define PLAYER4_SPRITE_PATTERN_INDEX      108

#define PLAYER4_PATTERNS_PER_FRAME        4
#define PLAYER4_FRAME_COUNT               9
#define PLAYER4_SPRITE_PATTERN_COUNT      \
    (PLAYER4_FRAME_COUNT * PLAYER4_PATTERNS_PER_FRAME)

typedef enum
{
    PLAYER4_FRAME_IDLE = 0,

    PLAYER4_FRAME_DOWN_0,
    PLAYER4_FRAME_DOWN_1,

    PLAYER4_FRAME_UP_0,
    PLAYER4_FRAME_UP_1,

    PLAYER4_FRAME_LEFT_0,
    PLAYER4_FRAME_LEFT_1,

    PLAYER4_FRAME_RIGHT_0,
    PLAYER4_FRAME_RIGHT_1

} Player4Frame;

#define PLAYER4_GET_PATTERN(frame) \
    ((u8)(PLAYER4_SPRITE_PATTERN_INDEX + ((u8)(frame) * PLAYER4_PATTERNS_PER_FRAME)))

static const u8 g_Player4WalkDownFrames[] =
{
    PLAYER4_FRAME_DOWN_0,
    PLAYER4_FRAME_DOWN_1
};

static const u8 g_Player4WalkUpFrames[] =
{
    PLAYER4_FRAME_UP_0,
    PLAYER4_FRAME_UP_1
};

static const u8 g_Player4WalkLeftFrames[] =
{
    PLAYER4_FRAME_LEFT_0,
    PLAYER4_FRAME_LEFT_1
};

static const u8 g_Player4WalkRightFrames[] =
{
    PLAYER4_FRAME_RIGHT_0,
    PLAYER4_FRAME_RIGHT_1
};

static const u8 g_Player4SpritePatterns[] =
{
    // -------------------------------------------------------------------------
    // Frame 0: IDLE / frontal quieto
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x0C, 0x1F, 0x3F, 0x7F, 0x73, 0x7F, 0x3F, 0x1F,

    // Inferior izquierdo
    0x3F, 0x7F, 0xE7, 0xC7, 0x07, 0x0F, 0x18, 0x30,

    // Superior derecho
    0xC0, 0xE0, 0xF0, 0xF8, 0x38, 0xF8, 0xF0, 0xE0,

    // Inferior derecho
    0xF0, 0xF8, 0x9C, 0x8C, 0x80, 0xC0, 0x60, 0x30,


    // -------------------------------------------------------------------------
    // Frame 1: DOWN_0 / andando hacia abajo
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x0C, 0x1F, 0x3F, 0x7F, 0x73, 0x7F, 0x3F, 0x1F,

    // Inferior izquierdo
    0x3F, 0x7F, 0xE7, 0xC7, 0x07, 0x0E, 0x18, 0x30,

    // Superior derecho
    0xC0, 0xE0, 0xF0, 0xF8, 0x38, 0xF8, 0xF0, 0xE0,

    // Inferior derecho
    0xF0, 0xF8, 0x9C, 0x8C, 0x80, 0xC0, 0x40, 0x60,


    // -------------------------------------------------------------------------
    // Frame 2: DOWN_1 / andando hacia abajo
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x0C, 0x1F, 0x3F, 0x7F, 0x73, 0x7F, 0x3F, 0x1F,

    // Inferior izquierdo
    0x3F, 0x7F, 0xE7, 0xC7, 0x07, 0x06, 0x02, 0x06,

    // Superior derecho
    0xC0, 0xE0, 0xF0, 0xF8, 0x38, 0xF8, 0xF0, 0xE0,

    // Inferior derecho
    0xF0, 0xF8, 0x9C, 0x8C, 0x80, 0xE0, 0x18, 0x0C,


    // -------------------------------------------------------------------------
    // Frame 3: UP_0 / andando hacia arriba
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x0C, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F,

    // Inferior izquierdo
    0x3F, 0x7F, 0xE7, 0xC7, 0x07, 0x0E, 0x18, 0x30,

    // Superior derecho
    0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF0, 0xE0,

    // Inferior derecho
    0xF0, 0xF8, 0x9C, 0x8C, 0x80, 0xC0, 0x40, 0x60,


    // -------------------------------------------------------------------------
    // Frame 4: UP_1 / andando hacia arriba
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x0C, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F,

    // Inferior izquierdo
    0x3F, 0x7F, 0xE7, 0xC7, 0x07, 0x06, 0x02, 0x06,

    // Superior derecho
    0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF0, 0xE0,

    // Inferior derecho
    0xF0, 0xF8, 0x9C, 0x8C, 0x80, 0xE0, 0x18, 0x0C,


    // -------------------------------------------------------------------------
    // Frame 5: LEFT_0 / andando hacia la izquierda
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x18, 0x3F, 0x7F, 0xFF, 0xF3, 0xFF, 0x7E, 0x3E,

    // Inferior izquierdo
    0x7F, 0xFF, 0xEF, 0xCF, 0x1F, 0x3B, 0x62, 0xC3,

    // Superior derecho
    0x00, 0x00, 0x80, 0xC0, 0x80, 0x00, 0x00, 0x00,

    // Inferior derecho
    0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,


    // -------------------------------------------------------------------------
    // Frame 6: LEFT_1 / andando hacia la izquierda
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x18, 0x3F, 0x7F, 0xFF, 0xF3, 0xFF, 0x7E, 0x3E,

    // Inferior izquierdo
    0x7F, 0xFF, 0xEF, 0xCF, 0x1F, 0x37, 0x43, 0xC1,

    // Superior derecho
    0x00, 0x00, 0x80, 0xC0, 0x80, 0x00, 0x00, 0x00,

    // Inferior derecho
    0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,


    // -------------------------------------------------------------------------
    // Frame 7: RIGHT_0 / andando hacia la derecha
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00,

    // Inferior izquierdo
    0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,

    // Superior derecho
    0x18, 0xFC, 0xFE, 0xFF, 0xCF, 0xFF, 0x7E, 0x7C,

    // Inferior derecho
    0xFE, 0xFF, 0xF7, 0xF3, 0xF8, 0xDC, 0x46, 0xC3,


    // -------------------------------------------------------------------------
    // Frame 8: RIGHT_1 / andando hacia la derecha
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00,

    // Inferior izquierdo
    0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,

    // Superior derecho
    0x18, 0xFC, 0xFE, 0xFF, 0xCF, 0xFF, 0x7E, 0x7C,

    // Inferior derecho
    0xFE, 0xFF, 0xF7, 0xF3, 0xF8, 0xEC, 0xC2, 0x83
};

#endif