# Manual del módulo `vdp` de MSXgl

## Qué es el módulo `vdp`

El módulo `vdp` es el núcleo gráfico de MSXgl. Se encarga de:

- modos de pantalla,
- acceso a VRAM,
- registros del VDP,
- sprites,
- y funciones avanzadas del chip de vídeo en máquinas superiores a MSX1.

Para usarlo en un proyecto:

- incluye `vdp.h`,
- y añade `"vdp"` a `LibModules` en `project_config.js`.

---

## Configuración previa en `msxgl_config.h`

El módulo `vdp` se adapta a la máquina y a los modos que vas a utilizar. Las opciones más importantes son:

- `VDP_VRAM_ADDR_14` para MSX1 con 16 KB de VRAM
- `VDP_VRAM_ADDR_17` para MSX2+ con 128 KB de VRAM
- `VDP_UNIT_*` para decidir el tipo usado en coordenadas
- `VDP_USE_MODE_*` para activar solo los modos que realmente necesitas

Ejemplo razonable para **MSX1 + SCREEN 2**:

```c
#define VDP_VRAM_ADDR VDP_VRAM_ADDR_14
#define VDP_UNIT VDP_UNIT_U8
#define VDP_USE_MODE_G2 TRUE
#define VDP_USE_MODE_G1 FALSE
#define VDP_USE_MODE_T1 FALSE
#define VDP_USE_MODE_MC FALSE
```

En un juego MSX1 conviene activar solo lo imprescindible para ahorrar código y mantener el proyecto más limpio.

---

# Funciones del módulo `vdp`

## 1. Inicialización y utilidades básicas

### `VDP_Initialize()`

Inicializa el módulo VDP y recupera valores iniciales desde BIOS.

**Uso:**

```c
VDP_Initialize();
```

**Cuándo usarla:**

- al arrancar si quieres inicializar explícitamente el módulo,
- o no llamarla si luego usas `VDP_SetMode()` y tienes activada la auto-inicialización.

---

### `VDP_GetVersion()`

Devuelve la versión del VDP detectada.

**Uso:**

```c
u8 vdpVersion = VDP_GetVersion();
```

**Cuándo usarla:**

- para distinguir entre MSX1, MSX2 y superiores,
- para activar o desactivar lógica según la máquina.

---

### `VDP_ClearVRAM()`

Borra la VRAM completa.

**Uso:**

```c
VDP_ClearVRAM();
```

**Cuándo usarla:**

- al iniciar una pantalla,
- al reiniciar un nivel,
- antes de cargar tablas nuevas.

---

## 2. Modo de pantalla

### `VDP_SetMode(mode)`

Cambia el modo de pantalla usando el enum `VDP_MODE`.

**Uso:**

```c
VDP_SetMode(VDP_MODE_SCREEN2);
```

**Cuándo usarla:**

- al arrancar el juego,
- al pasar de menú a juego,
- al cambiar de una pantalla a otra.

---

### `VDP_GetMode()`

Devuelve el modo actual.

**Uso:**

```c
u8 mode = VDP_GetMode();
```

---

### `VDP_IsBitmapMode(mode)`

Indica si el modo recibido es de tipo bitmap.

**Uso:**

```c
if (VDP_IsBitmapMode(VDP_GetMode()))
{
    /* lógica para modos bitmap */
}
```

---

### `VDP_IsPatternMode(mode)`

Indica si el modo recibido es de tipo patrón / texto.

**Uso:**

```c
if (VDP_IsPatternMode(VDP_GetMode()))
{
    /* lógica para modos por patrones */
}
```

---

### `VDP_SetModeFlag(flag)`

Escribe directamente el flag binario del modo.

**Recomendación:**  
En un proyecto normal conviene usar `VDP_SetMode()` en vez de esta función, salvo que sepas exactamente qué bits y qué tablas necesitas para ese modo.

---

## 3. Acceso a registros y estado del VDP

### `VDP_RegWrite(reg, value)`

Escribe un valor en un registro del VDP.

**Uso:**

```c
VDP_RegWrite(7, 0xF1);
```

**Cuándo usarla:**

- cuando necesitas modificar un registro concreto,
- para casos especiales no cubiertos por helpers de más alto nivel.

---

### `VDP_RegWriteBak(reg, value)`

Escribe el registro y además actualiza la copia interna que mantiene MSXgl.

**Uso:**

```c
VDP_RegWriteBak(7, 0xF1);
```

---

### `VDP_RegWriteBakMask(idx, mask, value)`

Modifica solo ciertos bits del registro usando una máscara.

**Uso:**

```c
VDP_RegWriteBakMask(1, 0x40, 0x40);
```

**Muy útil para:**

- activar o desactivar flags sin alterar los demás bits del mismo registro.

---

### `VDP_ReadDefaultStatus()`

Lee el registro de estado por defecto.

**Uso:**

```c
u8 status = VDP_ReadDefaultStatus();
```

---

### `VDP_ReadStatus(stat)`

Lee un registro de estado concreto. Esta función es más relevante en MSX2 o superior.

**Uso:**

```c
u8 status = VDP_ReadStatus(0);
```

---

## 4. Acceso a VRAM

Este bloque es uno de los más importantes para MSX1.

### `VDP_WriteVRAM_16K(src, dest, count)`

Copia bytes desde RAM a VRAM.

**Uso:**

```c
VDP_WriteVRAM_16K(patterns, 0x0000, 2048);
```

**Uso típico:**

- cargar patrones,
- cargar tabla de nombres,
- cargar tabla de colores,
- cargar patrones de sprites.

---

### `VDP_FillVRAM_16K(value, dest, count)`

Rellena una zona de VRAM con un valor fijo.

**Uso:**

```c
VDP_FillVRAM_16K(0x00, 0x1800, 768);
```

**Uso típico:**

- limpiar la name table,
- poner una tabla a cero,
- inicializar zonas de atributos.

---

### `VDP_FastFillVRAM_16K(value, dest, count)`

Versión rápida del relleno de VRAM.

**Uso:**

```c
VDP_FastFillVRAM_16K(0x00, 0x1800, 768);
```

---

### `VDP_ReadVRAM_16K(src, dest, count)`

Lee bytes desde VRAM a RAM.

**Uso:**

```c
VDP_ReadVRAM_16K(0x1800, buffer, 32);
```

**Uso típico:**

- depuración,
- lectura puntual de tablas,
- comprobaciones durante desarrollo.

---

### `VDP_Poke_16K(val, dest)`

Escribe un solo byte en VRAM.

**Uso:**

```c
VDP_Poke_16K(tile, 0x1800 + y * 32 + x);
```

**Uso típico:**

- cambiar una celda concreta del mapa,
- modificar un atributo puntual,
- actualizar rápidamente un elemento visual.

---

### `VDP_Peek_16K(src)`

Lee un solo byte de VRAM.

**Uso:**

```c
u8 value = VDP_Peek_16K(0x1800 + y * 32 + x);
```

---

### Macros genéricos: `VDP_WriteVRAM`, `VDP_FillVRAM`, `VDP_ReadVRAM`, `VDP_Poke`, `VDP_Peek`

MSXgl también ofrece nombres genéricos para no atarte a 16 KB o 128 KB.

**Ejemplo:**

```c
VDP_WriteVRAM(data, addrLow, addrHigh, count);
VDP_Poke(value, addrLow, addrHigh);
```

En MSX1, la configuración de 14 bits hace que esto quede adaptado al hardware correspondiente.

**Recomendación práctica:**  
Si quieres escribir código más portable dentro del ecosistema MSXgl, usa las funciones genéricas. Si quieres dejar muy claro que tu proyecto es MSX1 puro, puedes usar las variantes `_16K`.

---

## 5. Configuración de display

### `VDP_EnableDisplay(enable)`

Activa o desactiva la salida visible de la pantalla.

**Uso:**

```c
VDP_EnableDisplay(FALSE);
/* cambios masivos en VRAM */
VDP_EnableDisplay(TRUE);
```

**Muy útil para:**

- evitar parpadeos mientras modificas muchas tablas,
- hacer cambios grandes de pantalla de forma limpia.

---

### `VDP_EnableVBlank(enable)`

Activa o desactiva la interrupción vertical.

**Uso:**

```c
VDP_EnableVBlank(TRUE);
```

---

### `VDP_SetColor(color)`

Configura el color por defecto usando un byte con formato combinado.

**Uso:**

```c
VDP_SetColor(0xF1);
```

---

### `VDP_SetBackdropColor(color)`

Cambia el color de fondo o borde.

**Uso:**

```c
VDP_SetBackdropColor(1);
```

---

### `VDP_SetColor2(bg, text)`

Versión más cómoda para indicar fondo y texto por separado.

**Uso:**

```c
VDP_SetColor2(1, 15);
```

---

## 6. Funciones avanzadas más orientadas a MSX2 / MSX2+

Estas funciones forman parte del módulo, pero para un proyecto MSX1 normalmente no serán prioritarias:

- `VDP_EnableSprite()`
- `VDP_DisableSprite()`
- `VDP_EnableTransparency()`
- `VDP_EnableHBlank()`
- `VDP_SetHBlankLine()`
- `VDP_SetVerticalOffset()`
- `VDP_SetAdjustOffset()`
- `VDP_SetAdjustOffsetXY()`
- `VDP_SetGrayScale()`
- `VDP_SetFrequency()`
- `VDP_GetFrequency()`
- `VDP_SetLineCount()`
- `VDP_SetPageAlternance()`
- `VDP_SetInterlace()`
- `VDP_SetFrameRender()`
- `VDP_ResetVRAMAddrMSB()`
- `VDP_SetPalette()`
- `VDP_SetPaletteEntry()`
- `VDP_SetYJK()`
- `VDP_ExpendCommand()`
- `VDP_EnableMask()`
- `VDP_SetHorizontalOffset()`
- `VDP_SetHorizontalMode()`

Para MSX1 basta con conocerlas de pasada y centrarse primero en modos, VRAM y tablas.

---

## 7. Direcciones de tablas en VRAM

El módulo `vdp` permite fijar la dirección de las tablas importantes del VDP.

### `VDP_SetLayoutTable(addr)`

Configura la dirección de la tabla de nombres o layout.

**Uso:**

```c
VDP_SetLayoutTable(VDP_G2_ADDR_NT);
```

---

### `VDP_SetLayoutTableEx(addr, r2)`

Versión extendida para indicar también el valor de registro correspondiente.

---

### `VDP_SetColorTable(addr)`

Configura la dirección de la tabla de colores.

**Uso:**

```c
VDP_SetColorTable(VDP_G2_ADDR_CT);
```

---

### `VDP_SetColorTableEx(addr, r3, r10)`

Versión extendida para la tabla de colores.

---

### `VDP_SetPatternTable(addr)`

Configura la dirección de la tabla de patrones.

**Uso:**

```c
VDP_SetPatternTable(VDP_G2_ADDR_PT);
```

---

### `VDP_SetPatternTableEx(addr, r4)`

Versión extendida para la tabla de patrones.

---

### `VDP_SetSpriteAttributeTable(addr)`

Configura la tabla de atributos de sprite.

**Uso:**

```c
VDP_SetSpriteAttributeTable(VDP_G2_ADDR_SAT);
```

---

### `VDP_SetSpritePatternTable(addr)`

Configura la tabla de patrones de sprite.

**Uso:**

```c
VDP_SetSpritePatternTable(VDP_G2_ADDR_SPT);
```

---

## 8. Ejemplos de uso en un proyecto MSX1

### Caso 1. Arrancar SCREEN 2 limpio

```c
VDP_Initialize();
VDP_SetMode(VDP_MODE_SCREEN2);
VDP_ClearVRAM();
```

Esto deja el VDP preparado, en el modo correcto y con la VRAM limpia.

---

### Caso 2. Cargar tiles del mapa

```c
VDP_SetPatternTable(VDP_G2_ADDR_PT);
VDP_SetColorTable(VDP_G2_ADDR_CT);
VDP_SetLayoutTable(VDP_G2_ADDR_NT);

VDP_WriteVRAM(tilePatterns, VDP_G2_ADDR_PT, 0, tilePatternsSize);
VDP_WriteVRAM(tileColors,   VDP_G2_ADDR_CT, 0, tileColorsSize);
VDP_WriteVRAM(tileMap,      VDP_G2_ADDR_NT, 0, tileMapSize);
```

Esto es exactamente el tipo de uso más importante en un juego basado en tiles.

---

### Caso 3. Cambiar una celda concreta del mapa

```c
VDP_Poke(tileIndex, VDP_G2_ADDR_NT + y * 32 + x, 0);
```

Esto sirve, por ejemplo, para:

- romper un bloque,
- pintar una bomba,
- borrar una bomba,
- cambiar el suelo,
- actualizar una explosión si la representas con tiles.

---

### Caso 4. Rellenar una tabla completa

```c
VDP_FillVRAM(0x00, VDP_G2_ADDR_NT, 0, 32 * 24);
```

Muy útil para limpiar o reinicializar una zona completa.

---

## 9. Qué parte del módulo `vdp` te importa de verdad para un juego tipo Bomb Mania

Si el proyecto es **MSX1 + SCREEN 2 + juego por rejilla**, yo me centraría primero en estas funciones:

1. `VDP_SetMode()`
2. `VDP_ClearVRAM()`
3. `VDP_SetPatternTable()`
4. `VDP_SetColorTable()`
5. `VDP_SetLayoutTable()`
6. `VDP_WriteVRAM()`
7. `VDP_Poke()`
8. `VDP_FillVRAM()`
9. `VDP_EnableDisplay()`
10. `VDP_SetColor()` o `VDP_SetColor2()`

Con eso ya puedes cubrir una gran parte del trabajo base del juego.

---

## 10. Orden recomendado para aprender el módulo

Yo lo aprendería en este orden:

1. `VDP_SetMode()`
2. `VDP_ClearVRAM()`
3. `VDP_WriteVRAM()`
4. `VDP_Poke()`
5. `VDP_FillVRAM()`
6. direcciones de tablas (`Layout`, `Pattern`, `Color`)
7. sprites

Ese orden encaja muy bien con un proyecto MSX1 real.

---

## 11. Conclusión

El módulo `vdp` de MSXgl es una pieza central. No hace magia por sí solo, pero te da justo lo que necesitas para:

- cambiar de modo gráfico,
- escribir y leer VRAM,
- configurar tablas del VDP,
- controlar colores,
- y preparar la base visual del juego.

Para un proyecto como un clon de Bomb Mania en MSX1, lo esencial es dominar primero:

- SCREEN 2,
- tablas de patrones, colores y layout,
- escritura en VRAM,
- cambios puntuales de tiles,
- y uso limpio de la VRAM desde el bucle del juego.

Una vez tengas eso controlado, ya puedes entrar en sprites, animaciones y efectos más complejos.
