/*
 * Exported with nin10kit v1.8
 * Invocation command was nin10kit --mode=sprites --for_bitmap --bpp=4 --transparent=FF00FF --resize 32x32 dog dog.gif 
 * Time-stamp: Friday 04/02/2021, 18:39:30
 * 
 * Image Information
 * -----------------
 * dog.gif (frame 0) 32@32
 * dog.gif (frame 1) 32@32
 * dog.gif (frame 2) 32@32
 * dog.gif (frame 3) 32@32
 * dog.gif (frame 4) 32@32
 * dog.gif (frame 5) 32@32
 * Transparent color: (255, 0, 255)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef DOG_H
#define DOG_H

#define DOG_PALETTE_TYPE (0 << 13)
#define DOG_DIMENSION_TYPE (1 << 6)

extern const unsigned short dog_palette[96];
#define DOG_PALETTE_SIZE 192
#define DOG_PALETTE_LENGTH 96

extern const unsigned short dog[1536];
#define DOG_SIZE 3072
#define DOG_LENGTH 1536

#define DOG0_PALETTE_ID (0 << 12)
#define DOG0_ID 512

#define DOG1_PALETTE_ID (1 << 12)
#define DOG1_ID 528

#define DOG2_PALETTE_ID (2 << 12)
#define DOG2_ID 544

#define DOG3_PALETTE_ID (3 << 12)
#define DOG3_ID 560

#define DOG4_PALETTE_ID (4 << 12)
#define DOG4_ID 576

#define DOG5_PALETTE_ID (5 << 12)
#define DOG5_ID 592

extern const unsigned short dog_frames[6];
#define DOG_FRAMES 6

#define DOG_SPRITE_SHAPE (0 << 14)
#define DOG_SPRITE_SIZE (2 << 14)

#endif

