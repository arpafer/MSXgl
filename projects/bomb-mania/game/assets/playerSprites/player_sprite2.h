#ifndef PLAYER_SPRITE2_H
#define PLAYER_SPRITE2_H

#include "msxgl.h"

// -----------------------------------------------------------------------------
// Player 2 - MSX1 sprite 16x16, 1 color
// -----------------------------------------------------------------------------
//
// Diferencia visual respecto al Player 1:
// - Casco más cuadrado
// - Antena lateral superior
// - Cuerpo más estrecho
// - Piernas más abiertas
// - Perfiles laterales menos redondeados
//
// Cada frame 16x16 ocupa 4 patrones de 8x8:
//
//   1) superior izquierdo
//   2) inferior izquierdo
//   3) superior derecho
//   4) inferior derecho
//
// -----------------------------------------------------------------------------

#define PLAYER2_SPRITE_PATTERN_INDEX      36

#define PLAYER2_PATTERNS_PER_FRAME        4
#define PLAYER2_FRAME_COUNT               9
#define PLAYER2_SPRITE_PATTERN_COUNT      \
    (PLAYER2_FRAME_COUNT * PLAYER2_PATTERNS_PER_FRAME)

typedef enum
{
    PLAYER2_FRAME_IDLE = 0,

    PLAYER2_FRAME_DOWN_0,
    PLAYER2_FRAME_DOWN_1,

    PLAYER2_FRAME_UP_0,
    PLAYER2_FRAME_UP_1,

    PLAYER2_FRAME_LEFT_0,
    PLAYER2_FRAME_LEFT_1,

    PLAYER2_FRAME_RIGHT_0,
    PLAYER2_FRAME_RIGHT_1

} Player2Frame;

#define PLAYER2_GET_PATTERN(frame) \
    ((u8)(PLAYER2_SPRITE_PATTERN_INDEX + ((u8)(frame) * PLAYER2_PATTERNS_PER_FRAME)))

static const u8 g_Player2WalkDownFrames[] =
{
    PLAYER2_FRAME_DOWN_0,
    PLAYER2_FRAME_DOWN_1
};

static const u8 g_Player2WalkUpFrames[] =
{
    PLAYER2_FRAME_UP_0,
    PLAYER2_FRAME_UP_1
};

static const u8 g_Player2WalkLeftFrames[] =
{
    PLAYER2_FRAME_LEFT_0,
    PLAYER2_FRAME_LEFT_1
};

static const u8 g_Player2WalkRightFrames[] =
{
    PLAYER2_FRAME_RIGHT_0,
    PLAYER2_FRAME_RIGHT_1
};

static const u8 g_Player2SpritePatterns[] =
{
    // -------------------------------------------------------------------------
// Frame 0: IDLE / frontal quieto
// Player 2: casco cuadrado, antenas pequeñas, cuerpo compacto
// -------------------------------------------------------------------------

// Superior izquierdo
0x08, 0x1C, 0x3F, 0x3F, 0x33, 0x3F, 0x3F, 0x1F,

// Inferior izquierdo
0x07, 0x0F, 0x1F, 0x33, 0x61, 0x01, 0x03, 0x06,

// Superior derecho
0x10, 0x38, 0xFC, 0xFC, 0xCC, 0xFC, 0xFC, 0xF8,

// Inferior derecho
0xE0, 0xF0, 0xF8, 0xCC, 0x86, 0x80, 0xC0, 0x60,


    // -------------------------------------------------------------------------
    // Frame 1: DOWN_0 / andando hacia abajo
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x02, 0x07, 0x1F, 0x3F, 0x3B, 0x3F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x0F, 0x1F, 0x1B, 0x0F, 0x0F, 0x1B, 0x07, 0x0C,

    // Superior derecho
    0x00, 0xE0, 0xF8, 0xFC, 0xDC, 0xFC, 0xF8, 0xF0,

    // Inferior derecho
    0xF0, 0xF8, 0xD8, 0xF0, 0xF0, 0xD8, 0x80, 0x30,


    // -------------------------------------------------------------------------
    // Frame 2: DOWN_1 / andando hacia abajo
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x02, 0x07, 0x1F, 0x3F, 0x3B, 0x3F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x0F, 0x1F, 0x1B, 0x0F, 0x0F, 0x1B, 0x01, 0x06,

    // Superior derecho
    0x00, 0xE0, 0xF8, 0xFC, 0xDC, 0xFC, 0xF8, 0xF0,

    // Inferior derecho
    0xF0, 0xF8, 0xD8, 0xF0, 0xF0, 0xD8, 0xE0, 0x30,


    // -------------------------------------------------------------------------
    // Frame 3: UP_0 / andando hacia arriba
    // Casco cuadrado sin “cara”
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x02, 0x07, 0x1F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x0F, 0x1F, 0x1F, 0x0F, 0x0F, 0x1B, 0x07, 0x0C,

    // Superior derecho
    0x00, 0xE0, 0xF8, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0,

    // Inferior derecho
    0xF0, 0xF8, 0xF8, 0xF0, 0xF0, 0xD8, 0x80, 0x30,


    // -------------------------------------------------------------------------
    // Frame 4: UP_1 / andando hacia arriba
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x02, 0x07, 0x1F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x0F, 0x1F, 0x1F, 0x0F, 0x0F, 0x1B, 0x01, 0x06,

    // Superior derecho
    0x00, 0xE0, 0xF8, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0,

    // Inferior derecho
    0xF0, 0xF8, 0xF8, 0xF0, 0xF0, 0xD8, 0xE0, 0x30,


    // -------------------------------------------------------------------------
    // Frame 5: LEFT_0 / andando hacia la izquierda
    // Perfil claramente distinto: antena y mochila/joroba trasera
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x04, 0x0F, 0x1F, 0x3F, 0x3F, 0x3B, 0x1F, 0x0F,

    // Inferior izquierdo
    0x0F, 0x1F, 0x3F, 0x1F, 0x1F, 0x0F, 0x06, 0x0C,

    // Superior derecho
    0x00, 0xC0, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0x00,

    // Inferior derecho
    0x80, 0xC0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00,


    // -------------------------------------------------------------------------
    // Frame 6: LEFT_1 / andando hacia la izquierda
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x04, 0x0F, 0x1F, 0x3F, 0x3F, 0x3B, 0x1F, 0x0F,

    // Inferior izquierdo
    0x0F, 0x1F, 0x3F, 0x1F, 0x1F, 0x0F, 0x03, 0x06,

    // Superior derecho
    0x00, 0xC0, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0x00,

    // Inferior derecho
    0x80, 0xC0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00,


    // -------------------------------------------------------------------------
    // Frame 7: RIGHT_0 / andando hacia la derecha
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x03, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00,

    // Inferior izquierdo
    0x01, 0x03, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00,

    // Superior derecho
    0x20, 0xF0, 0xF8, 0xFC, 0xFC, 0xDC, 0xF8, 0xF0,

    // Inferior derecho
    0xF0, 0xF8, 0xFC, 0xF8, 0xF8, 0xF0, 0x60, 0x30,


    // -------------------------------------------------------------------------
    // Frame 8: RIGHT_1 / andando hacia la derecha
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x03, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00,

    // Inferior izquierdo
    0x01, 0x03, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00,

    // Superior derecho
    0x20, 0xF0, 0xF8, 0xFC, 0xFC, 0xDC, 0xF8, 0xF0,

    // Inferior derecho
    0xF0, 0xF8, 0xFC, 0xF8, 0xF8, 0xF0, 0xC0, 0x60
};

#endif