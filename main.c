#include "main.h"
#include "images/octopus.h"
#include "images/coin.h"

OamEntry shadow[128];

enum gba_state {
  START,
  PLAY,
  WIN,
  WIN_SHOW,
  LOSE,
  LOSE_SHOW,
};

struct object dog_sprite;
struct play play_state;

int main(void) {
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  initialize_screen();
  dog_sprite = default_dog;
  play_state = default_state;

  while (1) {
    waitForVBlank();
    currentButtons = BUTTONS; // Load the current state of the buttons

    if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
      state = START;
      reset_screen();
    }

    switch (state) {
    case START:
      draw_welcome_screen();
      if (KEY_DOWN(BUTTON_START, currentButtons) & ~previousButtons) {
        state = PLAY;
        drawFullScreenImageDMA(night);
        drawImageDMA(coin1_y, coin1_x, COIN_WIDTH, COIN_HEIGHT, coin);
        drawImageDMA(coin2_y, coin2_x, COIN_WIDTH, COIN_HEIGHT, coin);
        drawImageDMA(coin3_y, coin3_x, COIN_WIDTH, COIN_HEIGHT, coin);
      }
      break;
    case PLAY: {
      int result = draw_play_screen(previousButtons, currentButtons,
                                    &dog_sprite, &play_state);
      if (result == 1) {
        state = LOSE;
      } else if (result == 2) {
        state = WIN;
      }
      break;
    }

    case WIN:
      reset_screen();
      state = WIN_SHOW;
      break;
    case WIN_SHOW:
      draw_win_screen();
      if (KEY_DOWN(BUTTON_START, currentButtons) & ~previousButtons) {
        state = PLAY;
        drawFullScreenImageDMA(night);
        drawImageDMA(coin1_y, coin1_x, COIN_WIDTH, COIN_HEIGHT, coin);
        drawImageDMA(coin2_y, coin2_x, COIN_WIDTH, COIN_HEIGHT, coin);
        drawImageDMA(coin3_y, coin3_x, COIN_WIDTH, COIN_HEIGHT, coin);
      }
      break;
    case LOSE:
      reset_screen();
      state = LOSE_SHOW;
      break;
    case LOSE_SHOW:
      draw_lose_screen();
      if (KEY_DOWN(BUTTON_START, currentButtons) & ~previousButtons) {
        state = PLAY;
        drawFullScreenImageDMA(night);
        drawImageDMA(coin1_y, coin1_x, COIN_WIDTH, COIN_HEIGHT, coin);
        drawImageDMA(coin2_y, coin2_x, COIN_WIDTH, COIN_HEIGHT, coin);
        drawImageDMA(coin3_y, coin3_x, COIN_WIDTH, COIN_HEIGHT, coin);
      }
    }

    previousButtons = currentButtons; // Store the current state of the buttons

    DMA[3].src = shadow;
    DMA[3].dst = OAMMEM;
    DMA[3].cnt = 128 * 4 | DMA_ON;
  }

  return 0;
}

void reset_screen(void) {
  dog_sprite = default_dog;
  play_state = default_state;
  fillScreenDMA(BLACK);
  for (int i = 0; i < 128; i++) {
    shadow[i].attr0 = ATTR0_HIDE;
  }
}

void draw_welcome_screen(void) {
  drawImageDMA(HEIGHT - OCTOPUS_HEIGHT, WIDTH - OCTOPUS_WIDTH, OCTOPUS_WIDTH,
               OCTOPUS_HEIGHT, octopus);
  drawCenteredString(HEIGHT / 2, WIDTH / 2, 0, 0, "Generic Platformer",
                     0x0fd0); // A nice green
  drawCenteredString(HEIGHT / 2 + 15, WIDTH / 2, 0, 0, "Press Start to Play",
                     0x00ff); // red
}

void draw_lose_screen(void) {
  drawImageDMA(HEIGHT - GHOST_HEIGHT, WIDTH - GHOST_WIDTH, GHOST_WIDTH,
               GHOST_HEIGHT, ghost);
  drawCenteredString(HEIGHT / 2, WIDTH / 2, 0, 0, "You Lost :(",
                     0x0fd0); // A nice green
  drawCenteredString(HEIGHT / 2 + 15, WIDTH / 2, 0, 0,
                     "Press Start to Play Again",
                     0x00ff); // red
}

void draw_win_screen(void) {
  drawImageDMA(HEIGHT - OCTOPUS_HEIGHT, WIDTH - OCTOPUS_WIDTH, OCTOPUS_WIDTH,
               OCTOPUS_HEIGHT, octopus);
  drawCenteredString(HEIGHT / 2, WIDTH / 2, 0, 0, "You Won !!!",
                     0x0fd0); // A nice green
  drawCenteredString(HEIGHT / 2 + 15, WIDTH / 2, 0, 0,
                     "Press Start to Play Again",
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
