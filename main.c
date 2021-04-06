#include "main.h"
#include "play_screen.h"

OamEntry shadow[128];

enum gba_state {
  START,
  PLAY,
  WIN,
  LOSE,
};

int main(void) {
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  initialize_screen();

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
      draw_play_screen(previousButtons, currentButtons);
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


void initialize_screen(void) {
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
}
