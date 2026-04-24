#ifndef PLAYER_SPRITE3_H
#define PLAYER_SPRITE3_H

#include "msxgl.h"

// -----------------------------------------------------------------------------
// Player 3 - MSX1 sprite 16x16, 1 color
// -----------------------------------------------------------------------------
//
// Silueta:
// - Personaje compacto.
// - Antena vertical centrada.
// - Menos estrecho que la versión anterior.
// - Diferente de Player 1 y Player 2, pero sin parecer un bicho raro.
//
// Índice base:
// - Player 1 usa 0..35
// - Player 2 usa 36..71
// - Player 3 usa 72..107
//
// Cada frame 16x16 ocupa 4 patrones de 8x8:
//
//   1) superior izquierdo
//   2) inferior izquierdo
//   3) superior derecho
//   4) inferior derecho
//
// -----------------------------------------------------------------------------

#define PLAYER3_SPRITE_PATTERN_INDEX      72

#define PLAYER3_PATTERNS_PER_FRAME        4
#define PLAYER3_FRAME_COUNT               9
#define PLAYER3_SPRITE_PATTERN_COUNT      \
    (PLAYER3_FRAME_COUNT * PLAYER3_PATTERNS_PER_FRAME)

typedef enum
{
    PLAYER3_FRAME_IDLE = 0,

    PLAYER3_FRAME_DOWN_0,
    PLAYER3_FRAME_DOWN_1,

    PLAYER3_FRAME_UP_0,
    PLAYER3_FRAME_UP_1,

    PLAYER3_FRAME_LEFT_0,
    PLAYER3_FRAME_LEFT_1,

    PLAYER3_FRAME_RIGHT_0,
    PLAYER3_FRAME_RIGHT_1

} Player3Frame;

#define PLAYER3_GET_PATTERN(frame) \
    ((u8)(PLAYER3_SPRITE_PATTERN_INDEX + ((u8)(frame) * PLAYER3_PATTERNS_PER_FRAME)))

static const u8 g_Player3WalkDownFrames[] =
{
    PLAYER3_FRAME_DOWN_0,
    PLAYER3_FRAME_DOWN_1
};

static const u8 g_Player3WalkUpFrames[] =
{
    PLAYER3_FRAME_UP_0,
    PLAYER3_FRAME_UP_1
};

static const u8 g_Player3WalkLeftFrames[] =
{
    PLAYER3_FRAME_LEFT_0,
    PLAYER3_FRAME_LEFT_1
};

static const u8 g_Player3WalkRightFrames[] =
{
    PLAYER3_FRAME_RIGHT_0,
    PLAYER3_FRAME_RIGHT_1
};

static const u8 g_Player3SpritePatterns[] =
{
    // -------------------------------------------------------------------------
    // Frame 0: IDLE / frontal quieto
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x01, 0x01, 0x03, 0x07, 0x0F, 0x1D, 0x1F, 0x0F,

    // Inferior izquierdo
    0x07, 0x0F, 0x1F, 0x3B, 0x33, 0x03, 0x06, 0x0C,

    // Superior derecho
    0x80, 0x80, 0xC0, 0xE0, 0xF0, 0xB8, 0xF8, 0xF0,

    // Inferior derecho
    0xE0, 0xF0, 0xF8, 0x70, 0x30, 0xC0, 0x60, 0x30,


    // -------------------------------------------------------------------------
    // Frame 1: DOWN_0 / andando hacia abajo
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x01, 0x01, 0x03, 0x07, 0x0F, 0x1D, 0x1F, 0x0F,

    // Inferior izquierdo
    0x07, 0x0F, 0x1F, 0x3B, 0x33, 0x03, 0x0E, 0x18,

    // Superior derecho
    0x80, 0x80, 0xC0, 0xE0, 0xF0, 0xB8, 0xF8, 0xF0,

    // Inferior derecho
    0xE0, 0xF0, 0xF8, 0x70, 0x30, 0xC0, 0x30, 0x18,


    // -------------------------------------------------------------------------
    // Frame 2: DOWN_1 / andando hacia abajo
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x01, 0x01, 0x03, 0x07, 0x0F, 0x1D, 0x1F, 0x0F,

    // Inferior izquierdo
    0x07, 0x0F, 0x1F, 0x3B, 0x33, 0x03, 0x06, 0x0C,

    // Superior derecho
    0x80, 0x80, 0xC0, 0xE0, 0xF0, 0xB8, 0xF8, 0xF0,

    // Inferior derecho
    0xE0, 0xF0, 0xF8, 0x70, 0x30, 0xC0, 0x38, 0x0C,


    // -------------------------------------------------------------------------
    // Frame 3: UP_0 / andando hacia arriba
    // Cabeza sin huecos internos para representar la espalda/casco.
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x01, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x07, 0x0F, 0x1F, 0x3F, 0x33, 0x03, 0x0E, 0x18,

    // Superior derecho
    0x80, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xF0,

    // Inferior derecho
    0xE0, 0xF0, 0xF8, 0xF8, 0x30, 0xC0, 0x30, 0x18,


    // -------------------------------------------------------------------------
    // Frame 4: UP_1 / andando hacia arriba
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x01, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x07, 0x0F, 0x1F, 0x3F, 0x33, 0x03, 0x06, 0x0C,

    // Superior derecho
    0x80, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xF0,

    // Inferior derecho
    0xE0, 0xF0, 0xF8, 0xF8, 0x30, 0xC0, 0x38, 0x0C,


    // -------------------------------------------------------------------------
    // Frame 5: LEFT_0 / andando hacia la izquierda
    // Perfil izquierdo compacto con antena.
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x3F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x1F, 0x3F, 0x7F, 0x77, 0x27, 0x07, 0x0C, 0x18,

    // Superior derecho
    0x00, 0x00, 0xC0, 0xE0, 0xE0, 0x80, 0x80, 0x80,

    // Inferior derecho
    0x80, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0xC0, 0x60,


    // -------------------------------------------------------------------------
    // Frame 6: LEFT_1 / andando hacia la izquierda
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x3F, 0x1F, 0x0F,

    // Inferior izquierdo
    0x1F, 0x3F, 0x7F, 0x77, 0x27, 0x07, 0x1C, 0x30,

    // Superior derecho
    0x00, 0x00, 0xC0, 0xE0, 0xE0, 0x80, 0x80, 0x80,

    // Inferior derecho
    0x80, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x60, 0x30,


    // -------------------------------------------------------------------------
    // Frame 7: RIGHT_0 / andando hacia la derecha
    // Perfil derecho compacto con antena.
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x00, 0x03, 0x07, 0x07, 0x01, 0x01, 0x01,

    // Inferior izquierdo
    0x01, 0x03, 0x03, 0x01, 0x01, 0x01, 0x03, 0x06,

    // Superior derecho
    0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xF8, 0xF0,

    // Inferior derecho
    0xF8, 0xFC, 0xFE, 0xEE, 0xE4, 0xE0, 0x30, 0x18,


    // -------------------------------------------------------------------------
    // Frame 8: RIGHT_1 / andando hacia la derecha
    // -------------------------------------------------------------------------

    // Superior izquierdo
    0x00, 0x00, 0x03, 0x07, 0x07, 0x01, 0x01, 0x01,

    // Inferior izquierdo
    0x01, 0x03, 0x03, 0x01, 0x01, 0x01, 0x06, 0x0C,

    // Superior derecho
    0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xF8, 0xF0,

    // Inferior derecho
    0xF8, 0xFC, 0xFE, 0xEE, 0xE4, 0xE0, 0x38, 0x0C
};

#endif