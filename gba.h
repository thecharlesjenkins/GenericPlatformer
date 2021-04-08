#ifndef GBA_H
#define GBA_H

// ---------------------------------------------------------------------------
//                       USEFUL TYPEDEFS
// ---------------------------------------------------------------------------
/* An unsigned 32-bit (4-byte) type */
typedef unsigned int u32;
/* An signed 32-bit (4-byte) type */
typedef signed int s32;

/* An unsigned 16-bit (2-byte) type */
typedef unsigned short u16;
/* An signed 16-bit (2-byte) type */
typedef signed short s16;

/* An unsigned 8-bit (1-byte) type. Note that this type cannot be written onto
 * RAM directly. */
typedef unsigned char u8;
/* An signed 8-bit (1-byte) type */
typedef signed char s8;

// ---------------------------------------------------------------------------
//                       MODE3 MACROS
// ---------------------------------------------------------------------------
#define OFFSET(row, col, width) ((col) + (width) * (row))

#define REG_DISPCNT (*(volatile unsigned short *)0x4000000)
#define MODE3 3
#define BG2_ENABLE (1 << 10)
#define OBJ_ENABLE 0x1000 // Set bit 12 to 1 to enable sprites

#define COLOR(r, g, b) ((r) | (g) << 5 | (b) << 10)
#define WHITE COLOR(31, 31, 31)
#define RED COLOR(31, 0, 0)
#define GREEN COLOR(0, 31, 0)
#define BLUE COLOR(0, 0, 31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK COLOR(0, 0, 0)
#define GRAY COLOR(5, 5, 5)

// The size of the GBA Screen
#define WIDTH 240
#define HEIGHT 160

// This is initialized in gba.c
extern volatile unsigned short *videoBuffer;

// ---------------------------------------------------------------------------
//                       BUTTON INPUT
// ---------------------------------------------------------------------------
#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_SELECT (1 << 2)
#define BUTTON_START (1 << 3)
#define BUTTON_RIGHT (1 << 4)
#define BUTTON_LEFT (1 << 5)
#define BUTTON_UP (1 << 6)
#define BUTTON_DOWN (1 << 7)
#define BUTTON_R (1 << 8)
#define BUTTON_L (1 << 9)

#define BUTTONS (*(volatile u32 *)0x4000130)
#define KEY_DOWN(key, buttons) (~(buttons) & (key))

// TODO: COMPLETE THIS MACRO.
// Remember that a button is recently pressed if it wasn't pressed in the last
// input (oldButtons) but is pressed in the current input. Use the KEY_DOWN
// macro to check if the button was pressed in the inputs.
#define KEY_JUST_PRESSED(key, buttons, oldbuttons)                             \
  (KEY_DOWN((key), (buttons)) & (oldbuttons))

// ---------------------------------------------------------------------------
//                       DMA
// ---------------------------------------------------------------------------
typedef struct {
  const volatile void *src;
  const volatile void *dst;
  u32 cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *)0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

// ---------------------------------------------------------------------------
//                       VBLANK
// ---------------------------------------------------------------------------
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

// Use this variable to count vBlanks. Initialized in gba.c and to be
// manipulated by waitForVBlank()
extern u32 vBlankCounter;

/*
 * Runs a blocking loop until the start of next VBlank.
 */
void waitForVBlank(void);

// ---------------------------------------------------------------------------
//                       MISC
// ---------------------------------------------------------------------------
#define UNUSED(param) ((void)((param)))

/*
 * Generates a pseudo-random number between min and max, inclusive.
 *
 * @param  min bottom end of range.
 * @param  max top end of range.
 * @return random number in the given range.
 */
int randint(int min, int max);

// ---------------------------------------------------------------------------
//                       DRAWING
// ---------------------------------------------------------------------------
void setPixel(int row, int col, u16 color);
void drawRectDMA(int row, int col, int width, int height, volatile u16 color);
void drawFullScreenImageDMA(const u16 *image);
void drawImageDMA(int row, int col, int width, int height, const u16 *image);
void fillScreenDMA(volatile u16 color);
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);
void drawCenteredString(int row, int col, int width, int height, char *str,
                        u16 color);
void undrawChar(int row, int col, char ch, const u16 *image);
void undrawString(int row, int col, char *str, const u16 *image);

    /* Contains the pixels of each character from a 6x8 font */
    // This is in the font.c file. You can replace the font if you want.
    extern const unsigned char fontdata_6x8[12288];

// ---------------------------------------------------------------------------
//                       SPRITE CONTROL
// ---------------------------------------------------------------------------

// ATTRIBUTE 0

// Bits 8-9 flags Object Mode controls what type of sprite it is, and whether to
// draw or not (bit patterns 1 and 3 are used for affine sprites not explained
// in these slides).
#define ATTR0_REG (0 << 8) // Default
#define ATTR0_HIDE                                                             \
  (2 << 8) // If set the sprite is hidden, by default all sprites are SHOWN

// Bits A-B control Rendering modes.  Alpha blending can be enabled by setting
// these two bits to 01.

// C controls Mosaic effect if set the sprite will appear pixelated.
#define ATTR0_MOSAIC (1 << 12)

// D controls what type of palette the sprite is using (This define is given to
// you by nin10kit). E-F controls the shape of the sprite (This define is given
// to you by nin10kit).

// ATTRIBUTE 1
// Bottom 9 bits control the X coordinate. It is treated as a signed value, so
// in the case that is is negative the portion of the sprite that’s onscreen
// will be drawn.

// Bits 9-B has to do with Affine Sprites which is beyond the scope of this
// tutorial.

// C-D control whether the sprite appears flipped.
#define ATTR1_NOFLIP 0
#define ATTR1_HFLIP (1 << 12)
#define ATTR1_VFLIP (1 << 13)

// E-F controls the size of the sprite (This define given to you by nin10kit).

// ATTRIBUTE 2
// Bottom 10 bits control the starting tile id of the sprite.  This define is
// given to you by nin10kit.

// A-B control the priority of the sprite.  Smaller Priorities will be closer to
// the player and thus drawn on top.
#define PRIORITY(pri) ((pri) << 10)

// C-F only are important if your sprites are composed of 4 bpp tiles.  It
// controls which palette bank the sprite is used. (This define is given to you
// by nin10kit).

#define SPRITEPAL ((u16 *)0x5000200)

typedef struct {
  u16 attr0;
  u16 attr1;
  u16 attr2;
  u16 fill;
} OamEntry;

#define OAMMEM ((OamEntry *)0x7000000)

typedef struct {
  u16 fill0[3];
  s16 pa;
  u16 fill1[3];
  s16 pb;
  u16 fill2[3];
  s16 pc;
  u16 fill3[3];
  s16 pd;
} OBJ_AFFINE;

typedef struct {
  u16 tileimg[8192];
} charblock;

#define CHARBLOCKBASE ((charblock *)0x6000000)

#endif
