#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  PLAY,
  WIN,
  LOSE,
};

OamEntry shadow[128];

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE | OBJ_ENABLE | DOG_DIMENSION_TYPE;

  DMA[3].src = dog_palette;
  DMA[3].dst = SPRITEPAL;
  DMA[3].cnt = DOG_PALETTE_LENGTH | DMA_ON;

  DMA[3].src = dog;
  DMA[3].dst = &CHARBLOCKBASE[5];
  DMA[3].cnt = DOG_LENGTH | DMA_ON;

  for (int i = 0; i < 128; i++) {
    shadow[i].attr0 = ATTR0_HIDE;
  }

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  int delay = 0;
  int frame_delay = 5;
  int frame = 1;
  OamEntry *dog = shadow;
  while (1) {
    waitForVBlank();
    currentButtons = BUTTONS; // Load the current state of the buttons

    switch (state) {
    case START:
      draw_welcome_screen();
      if (KEY_DOWN(BUTTON_START, currentButtons) & ~previousButtons) {
        state = PLAY;
        drawFullScreenImageDMA(night);
      }
      break;
    case PLAY:
      dog->attr0 = 48 | DOG_PALETTE_TYPE | DOG_SPRITE_SHAPE;
      dog->attr1 = 88 | DOG_SPRITE_SIZE;
      dog->attr2 = DOG0_PALETTE_ID | dog_frames[0];
      if (delay > frame_delay) {
        delay = 0;
        frame = (frame + 1) % DOG_FRAMES;
      }
      delay++;

      int frame_ptr = dog_frames[frame];
      dog->attr2 = DOG0_PALETTE_ID | frame_ptr;
      break;
    case WIN:

      // state = ?
      break;
    case LOSE:

      // state = ?
      break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons

    DMA[3].src = shadow;
    DMA[3].dst = OAMMEM;
    DMA[3].cnt = 128 * 4 | DMA_ON;
  }

  return 0;
}

void draw_welcome_screen(void) {
  drawImageDMA(HEIGHT - GHOST_HEIGHT, WIDTH - GHOST_WIDTH, GHOST_WIDTH,
               GHOST_HEIGHT, ghost);
  drawCenteredString(HEIGHT / 2, WIDTH / 2, 0, 0, "Generic Platformer",
                     0x0fd0); // A nice green
  drawCenteredString(HEIGHT / 2 + 15, WIDTH / 2, 0, 0, "Press Start to Play",
                     0x00ff); // red
}

void draw_play_screen(OamEntry *dog, int *delay, int frame, int frame_delay) {
  dog->attr0 = 48 | DOG_PALETTE_TYPE | DOG_SPRITE_SHAPE;
  dog->attr1 = 88 | DOG_SPRITE_SIZE;
  dog->attr2 = DOG0_PALETTE_ID | dog_frames[0];
  if (*delay > frame_delay) {
    *delay = 0;
    frame = (frame + 1) % DOG_FRAMES;
  }
  (*delay)++;

  int frame_ptr = dog_frames[frame];
  dog->attr2 = DOG0_PALETTE_ID | frame_ptr;
}
