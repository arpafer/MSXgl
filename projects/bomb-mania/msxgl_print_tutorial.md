# Tutorial del módulo `print` de MSXgl

## 1. Qué es el módulo `print`

El módulo `print` de MSXgl sirve para mostrar texto en pantalla. Puede trabajar en varios modos de render:

- **Text**: dibuja caracteres como patrones en modos por tiles.
- **Bitmap**: dibuja caracteres desde RAM en modos bitmap.
- **Bitmap con transparencia**: igual que bitmap, pero respetando transparencia.
- **VRAM**: carga la fuente una vez en VRAM y luego dibuja usando copias en VRAM.
- **Sprites**: dibuja texto usando sprites.

Para usar este módulo:

- incluye `print.h`
- añade `"print"` a `LibModules` en `project_config.js`

> Dependencia: el módulo `print` depende de `vdp`.

---

## 2. Qué modo te interesa si trabajas en MSX1

Si tu proyecto es un juego para **MSX1**, normalmente te interesará sobre todo el modo **Text**, porque:

- es compatible con **SCREEN 0, 1, 2 y 4** en los modos basados en tiles,
- es el más natural para menús, HUD, textos y depuración,
- y encaja bien con juegos en **SCREEN 2**.

Los modos **Bitmap** y **VRAM** están pensados para pantallas bitmap de MSX2 o superior.

El modo **Sprites** sí puede usarse también en MSX1, pero suele ser más útil para efectos especiales o textos muy concretos, no para un sistema general de texto.

---

## 3. Opciones de configuración en `msxgl_config.h`

Estas son las opciones principales del módulo `print`:

```c
// Print module setting
#define PRINT_USE_TEXT             TRUE
#define PRINT_USE_BITMAP           FALSE
#define PRINT_USE_VRAM             FALSE
#define PRINT_USE_SPRITE           FALSE
#define PRINT_USE_FX_SHADOW        FALSE
#define PRINT_USE_FX_OUTLINE       FALSE
#define PRINT_USE_2_PASS_FX        FALSE
#define PRINT_USE_GRAPH            TRUE
#define PRINT_USE_VALIDATOR        TRUE
#define PRINT_USE_UNIT             FALSE
#define PRINT_USE_FORMAT           TRUE
#define PRINT_USE_32B              TRUE
#define PRINT_SKIP_SPACE           FALSE
#define PRINT_COLOR_NUM            12

#define PRINT_WIDTH                PRINT_WIDTH_1
#define PRINT_HEIGHT               PRINT_HEIGHT_1
```

## Recomendación para MSX1 + SCREEN 2

Para un proyecto MSX1 centrado en texto por tiles, una configuración sensata sería:

```c
#define PRINT_USE_TEXT             TRUE
#define PRINT_USE_BITMAP           FALSE
#define PRINT_USE_VRAM             FALSE
#define PRINT_USE_SPRITE           FALSE
#define PRINT_USE_FX_SHADOW        FALSE
#define PRINT_USE_FX_OUTLINE       FALSE
#define PRINT_USE_2_PASS_FX        FALSE
#define PRINT_USE_GRAPH            TRUE
#define PRINT_USE_VALIDATOR        TRUE
#define PRINT_USE_UNIT             FALSE
#define PRINT_USE_FORMAT           TRUE
#define PRINT_USE_32B              FALSE
#define PRINT_SKIP_SPACE           FALSE
#define PRINT_COLOR_NUM            1
#define PRINT_WIDTH                PRINT_WIDTH_1
#define PRINT_HEIGHT               PRINT_HEIGHT_1
```

### Qué hace cada opción importante

- `PRINT_USE_TEXT`: activa el modo texto por patrones. Es la opción clave en MSX1.
- `PRINT_USE_BITMAP`: activa texto bitmap desde RAM. Más orientado a MSX2+.
- `PRINT_USE_VRAM`: activa texto bitmap cargando primero la fuente en VRAM.
- `PRINT_USE_SPRITE`: activa texto usando sprites.
- `PRINT_USE_FX_SHADOW`: activa sombra.
- `PRINT_USE_FX_OUTLINE`: activa contorno.
- `PRINT_USE_2_PASS_FX`: mejora algunos efectos en bitmap evitando solapamientos.
- `PRINT_USE_GRAPH`: activa caracteres gráficos, líneas y cajas.
- `PRINT_USE_VALIDATOR`: activa caracteres validador.
- `PRINT_USE_UNIT`: permite imprimir enteros con sufijos de unidad o formatos adicionales.
- `PRINT_USE_FORMAT`: activa funciones tipo formato.
- `PRINT_USE_32B`: permite imprimir enteros de 32 bits.
- `PRINT_SKIP_SPACE`: cambia cómo se trata el carácter espacio.
- `PRINT_COLOR_NUM`: número de colores configurables por línea.
- `PRINT_WIDTH` y `PRINT_HEIGHT`: controlan el tamaño lógico del carácter.

---

## 4. Modos del módulo `print`

## 4.1. Modo Text

Dibuja caracteres como patrones en la tabla de nombres. Es el modo más importante en MSX1.

Ejemplo típico:

```c
#include "font/font_mgl_sample8.h"

VDP_SetMode(VDP_MODE_SCREEN1);
Print_SetTextFont(g_Font_MGL_Sample8, 1);
Print_SetPosition(10, 10);
Print_DrawText("Text mode");
```

### Cuándo usarlo

- textos de menú,
- marcador,
- mensajes,
- depuración,
- pantallas de presentación.

---

## 4.2. Modo Bitmap

Dibuja caracteres en tiempo real desde RAM. Pensado para modos bitmap de MSX2 o superior.

Ejemplo típico:

```c
#include "font/font_mgl_sample6.h"

VDP_SetMode(VDP_MODE_SCREEN5);
Print_SetBitmapFont(g_Font_MGL_Sample6);
Print_SetPosition(100, 100);
Print_DrawText("Bitmap mode");
```

---

## 4.3. Modo Bitmap con transparencia

Es una variante del bitmap normal, pero respetando la transparencia.

```c
Print_SetMode(PRINT_MODE_BITMAP_TRANS);
```

Este modo es algo más lento que el bitmap normal.

---

## 4.4. Modo VRAM

Sube la fuente una vez a VRAM y luego dibuja desde ahí. Inicializar cuesta más, pero dibujar luego es más rápido.

Ejemplo:

```c
#include "font/font_mgl_sample6.h"

Print_SetVRAMFont(g_Font_MGL_Sample6, 212, COLOR_WHITE);
Print_SetPosition(100, 150);
Print_DrawText("VRAM mode");
```

---

## 4.5. Modo Sprites

Dibuja texto utilizando sprites.

Ejemplo:

```c
#include "font/font_mgl_sample8.h"

VDP_SetMode(VDP_MODE_SCREEN1);
Print_SetSpriteFont(g_Font_MGL_Sample8, 0, 0);
Print_SetPosition(100, 50);
Print_DrawText("SPRT");
```

### Cuándo puede interesar

- efectos especiales,
- rótulos flotantes,
- textos cortos sobre el juego,
- elementos que deban moverse sin tocar el fondo.

---

## 5. Matriz de compatibilidad de modos

Resumen práctico de compatibilidad:

- **Text**: SCREEN 0, 1, 2 y 4
- **Bitmap**: SCREEN 5 a 8
- **VRAM**: SCREEN 5 a 8
- **Sprites**: SCREEN 1 a 8 y otros modos con sprites habilitados

Para **MSX1**, la opción más útil suele ser:

- **Text**
- y en algunos casos **Sprites**

---

## 6. Estructura interna del módulo

El módulo mantiene una estructura global `Print_Data` con información como:

- tamaño del patrón de carácter,
- tamaño lógico del carácter,
- posición actual del cursor,
- color de texto,
- color de fondo,
- rango ASCII de la fuente,
- modo actual de impresión,
- ancho de pantalla,
- datos de fuente,
- parámetros de sprite o VRAM según el modo.

No necesitas modificar esta estructura directamente en un uso normal. Lo habitual es usar las funciones del módulo para cambiar su estado.

---

## 7. Funciones principales del módulo `print`

## 7.1. Inicialización

### `Print_Initialize()`

Inicializa el módulo `print`.

```c
bool ok = Print_Initialize();
```

> Debe llamarse después de `VDP_SetMode()`.

### Cuándo usarla

- al empezar a usar el sistema de texto,
- después de configurar el modo gráfico.

---

## 7.2. Selección de modo

### `Print_SetMode(mode)`

Cambia el modo de impresión actual.

```c
Print_SetMode(PRINT_MODE_TEXT);
```

Valores posibles según configuración:

- `PRINT_MODE_BITMAP`
- `PRINT_MODE_BITMAP_TRANS`
- `PRINT_MODE_BITMAP_VRAM`
- `PRINT_MODE_SPRITE`
- `PRINT_MODE_TEXT`

### Recomendación

En MSX1, normalmente no necesitarás cambiar de modo constantemente. Lo normal será usar `PRINT_MODE_TEXT`.

---

## 7.3. Selección de fuente general

### `Print_SetFont(const u8* font)`

Configura la fuente actual.

```c
Print_SetFont(miFuente);
```

Esta es una función genérica. En la práctica, muchas veces usarás una de las funciones más específicas siguientes.

---

### `Print_SetFontEx(...)`

Permite configurar la fuente manualmente indicando:

- ancho real del patrón,
- alto real del patrón,
- ancho lógico,
- alto lógico,
- primer carácter ASCII,
- último carácter ASCII,
- tabla de patrones.

```c
Print_SetFontEx(8, 8, 1, 1, 32, 127, patterns);
```

### Cuándo usarla

- cuando quieras controlar exactamente la fuente,
- cuando construyas tus propias fuentes o herramientas.

---

### `Print_GetFontInfo()`

Devuelve la estructura actual de información de fuente.

```c
const Print_Data* info = Print_GetFontInfo();
```

Útil para inspección o lógica avanzada.

---

## 7.4. Posición del cursor

### `Print_SetPosition(x, y)`

Coloca el cursor de impresión.

```c
Print_SetPosition(10, 5);
```

En modo texto por tiles, `x` e `y` suelen interpretarse en unidades de rejilla.
En bitmap o sprites, suelen interpretarse en píxeles.

---

### `Print_SetPositionX(x)`

Cambia solo la coordenada X.

```c
Print_SetPositionX(8);
```

---

### `Print_SetPositionY(y)`

Cambia solo la coordenada Y.

```c
Print_SetPositionY(12);
```

---

## 7.5. Tamaño de carácter y tabulación

### `Print_SetCharSize(x, y)`

Define el tamaño lógico del carácter.

```c
Print_SetCharSize(1, 1);
```

En MSX1 con texto por tiles normalmente no tocarás mucho esto.

---

### `Print_SetTabSize(size)`

Define el tamaño del tabulador en píxeles.

```c
Print_SetTabSize(32);
```

Debe ser potencia de 2.

---

## 7.6. Fuentes por modo

### `Print_SetBitmapFont(const u8* font)`

Inicializa el módulo y configura una fuente bitmap desde RAM.

```c
Print_SetBitmapFont(g_Font_MGL_Sample6);
```

---

### `Print_SetVRAMFont(const u8* font, UY y, u8 color)`

Configura una fuente VRAM y la sube a VRAM.

```c
Print_SetVRAMFont(g_Font_MGL_Sample6, 212, COLOR_WHITE);
```

Parámetros:

- `font`: fuente
- `y`: posición Y donde se almacena en VRAM
- `color`: color de la fuente

---

### `Print_SetTextFont(const u8* font, u8 offset)`

Configura una fuente en modo texto y la sube como patrones.

```c
Print_SetTextFont(g_Font_MGL_Sample8, 1);
```

Parámetros:

- `font`: fuente
- `offset`: índice de patrón desde donde se cargará

### Esta es una de las funciones más importantes para MSX1.

---

### `Print_SelectTextFont(const u8* font, u8 offset)`

Selecciona una fuente para modo texto, ajustando su configuración interna.

```c
Print_SelectTextFont(g_Font_MGL_Sample8, 1);
```

---

### `Print_GetPatternOffset()`

Devuelve el offset de patrón actual de la fuente de texto.

```c
u8 offset = Print_GetPatternOffset();
```

---

### `Print_SetPatternOffset(u8 offset)`

Cambia el offset de patrón donde se considera cargada la fuente.

```c
Print_SetPatternOffset(1);
```

---

### `Print_SetSpriteFont(const u8* font, u8 patIdx, u8 sprtIdx)`

Carga una fuente en patrones de sprite.

```c
Print_SetSpriteFont(g_Font_MGL_Sample8, 0, 0);
```

Parámetros:

- `font`: fuente
- `patIdx`: índice inicial de patrón de sprite
- `sprtIdx`: índice inicial de sprite

---

### `Print_GetSpritePattern()`

Devuelve el índice inicial de patrón de sprite usado para la fuente.

```c
u8 pattern = Print_GetSpritePattern();
```

---

### `Print_GetSpriteID()`

Devuelve el índice de sprite actual.

```c
u8 id = Print_GetSpriteID();
```

---

### `Print_SetSpriteID(u8 id)`

Cambia el índice de sprite inicial.

```c
Print_SetSpriteID(4);
```

---

## 7.7. Dibujo básico

### `Print_DrawChar(u8 chr)`

Dibuja un único carácter.

```c
Print_DrawChar('A');
```

---

### `Print_DrawCharX(c8 chr, u8 num)`

Dibuja el mismo carácter varias veces.

```c
Print_DrawCharX('-', 10);
```

Muy útil para líneas simples.

---

### `Print_DrawText(const c8* string)`

Dibuja una cadena terminada en `\0`.

```c
Print_DrawText("Hola MSX");
```

Es la función más usada del módulo.

---

## 7.8. Dibujo de números y formatos simples

### `Print_DrawHex8(u8 value)`

Dibuja un valor de 8 bits en hexadecimal.

```c
Print_DrawHex8(0xAF);
```

---

### `Print_DrawHex16(u16 value)`

Dibuja un valor de 16 bits en hexadecimal.

```c
Print_DrawHex16(0x1234);
```

---

### `Print_DrawBin8(u8 value)`

Dibuja un valor de 8 bits en binario.

```c
Print_DrawBin8(0b10101010);
```

---

### `Print_DrawHex32(u32 value)`

Dibuja un valor de 32 bits en hexadecimal si `PRINT_USE_32B` está activado.

```c
Print_DrawHex32(0x12345678);
```

---

### `Print_DrawInt(...)`

Dibuja un entero decimal con signo.

Si `PRINT_USE_32B == TRUE`, usa entero de 32 bits.
Si `PRINT_USE_32B == FALSE`, usa entero de 16 bits.

```c
Print_DrawInt(1234);
Print_DrawInt(-25);
```

---

## 7.9. Espacios, tabulaciones y salto de línea

### `Print_Space()`

Avanza una posición de espacio.

```c
Print_Space();
```

---

### `Print_Tab()`

Avanza hasta la siguiente tabulación.

```c
Print_Tab();
```

---

### `Print_Return()`

Hace retorno de carro lógico:

- X vuelve a 0
- Y avanza una línea

```c
Print_Return();
```

---

## 7.10. Formato tipo printf

### `Print_DrawFormat(...)`

Permite imprimir texto con formato si `PRINT_USE_FORMAT` está activado.

La cabecera indica que esta función existe, aunque el detalle completo de formato depende de la implementación concreta del módulo.

Ejemplo conceptual:

```c
Print_DrawFormat("Puntos: %d", score);
```

### Recomendación

Úsalo con moderación en MSX1 si quieres mantener controlado el tamaño del binario.

---

## 8. Tutorial práctico mínimo para MSX1

Este es el flujo más razonable para usar `print` en un proyecto MSX1 con SCREEN 2.

## Paso 1. Configurar el módulo

En `msxgl_config.h`:

```c
#define PRINT_USE_TEXT     TRUE
#define PRINT_USE_BITMAP   FALSE
#define PRINT_USE_VRAM     FALSE
#define PRINT_USE_SPRITE   FALSE
#define PRINT_USE_FORMAT   TRUE
#define PRINT_USE_32B      FALSE
#define PRINT_WIDTH        PRINT_WIDTH_1
#define PRINT_HEIGHT       PRINT_HEIGHT_1
```

---

## Paso 2. Incluir cabeceras

```c
#include "vdp.h"
#include "print.h"
#include "font/font_mgl_sample8.h"
```

---

## Paso 3. Inicializar modo gráfico

```c
VDP_SetMode(VDP_MODE_SCREEN2);
```

---

## Paso 4. Inicializar print

```c
Print_Initialize();
```

---

## Paso 5. Cargar fuente de texto

```c
Print_SetTextFont(g_Font_MGL_Sample8, 1);
```

---

## Paso 6. Colocar cursor y escribir

```c
Print_SetPosition(2, 2);
Print_DrawText("BOMB MANIA");
```

---

## Paso 7. Mostrar números

```c
Print_SetPosition(2, 4);
Print_DrawText("TIME:");
Print_SetPosition(8, 4);
Print_DrawInt(99);
```

---

## 9. Ejemplo completo mínimo

```c
#include "vdp.h"
#include "print.h"
#include "font/font_mgl_sample8.h"

void main(void)
{
    VDP_SetMode(VDP_MODE_SCREEN2);
    Print_Initialize();
    Print_SetTextFont(g_Font_MGL_Sample8, 1);

    Print_SetPosition(2, 2);
    Print_DrawText("BOMB MANIA");

    Print_SetPosition(2, 4);
    Print_DrawText("TIME:");
    Print_SetPosition(8, 4);
    Print_DrawInt(99);

    while(1)
    {
    }
}
```

---

## 10. Qué funciones te importan de verdad en tu caso

Para un proyecto como el tuyo, yo me centraría sobre todo en estas funciones:

1. `Print_Initialize()`
2. `Print_SetTextFont()`
3. `Print_SetPosition()`
4. `Print_DrawText()`
5. `Print_DrawInt()`
6. `Print_DrawHex8()` y `Print_DrawHex16()` para depuración
7. `Print_Return()`
8. `Print_DrawCharX()` para líneas simples

Si más adelante haces un HUD especial o rótulos animados, entonces mirarías:

- `Print_SetSpriteFont()`
- `Print_SetMode()`
- `Print_SetSpriteID()`

---

## 11. Qué errores evitar

- usar `print` antes de haber hecho `VDP_SetMode()`
- no activar `PRINT_USE_TEXT` en MSX1
- usar modos bitmap en un proyecto pensado para MSX1
- usar `Print_DrawFormat()` por todas partes si quieres ahorrar tamaño
- cargar una fuente en modo texto sin reservar bien el `offset`

---

## 12. Conclusión

El módulo `print` de MSXgl es bastante flexible, pero en **MSX1** lo normal es aprovechar sobre todo:

- **modo Text** para HUD, menús y mensajes,
- y quizá **modo Sprite** en casos concretos.

Si dominas estas tres ideas:

- `Print_SetTextFont()`
- `Print_SetPosition()`
- `Print_DrawText()`

ya tienes resuelto casi todo el texto básico de un juego MSX1.
