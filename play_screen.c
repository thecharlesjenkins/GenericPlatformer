#include "play_screen.h"

play play_state;

// int surfaces[][] = {{}};

void initialize_play_screen(void) {
  play state = {shadow, 0, 0, 5, 1, 50, 150, 10, 0};
  play_state = state;
}

void draw_play_screen(u32 previousButtons, u32 currentButtons) {
  if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
    play_state.facing = 0;
    play_state.dx = 1;
  } else if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
    play_state.facing = 1;
    play_state.dx = -1;
  } else {
    play_state.dx = 0;
  }

  if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons) && play_state.dy == 0) {
    play_state.dy = 10;
  }

  play_state.dy += gravity;
  int next_loc_y = play_state.y - play_state.dy;
  int next_loc_x = play_state.x - play_state.dx;

  move(play_state.y, play_state.x, next_loc_y, next_loc_x);

  play_state.dog->attr0 = play_state.y | DOG_PALETTE_TYPE | DOG_SPRITE_SHAPE;
  play_state.dog->attr1 =
      play_state.x | DOG_SPRITE_SIZE | (play_state.facing << 12);

  if (KEY_DOWN((BUTTON_LEFT | BUTTON_RIGHT), currentButtons)) {
    play_state.dog->attr2 =
        play_state.frame << 12 | dog_frames[play_state.frame];

    if (play_state.delay > play_state.frame_delay) {
      play_state.delay = 0;
      play_state.frame = (play_state.frame + 1) % DOG_FRAMES;
    }
    (play_state.delay)++;
  } else {
    play_state.delay = 0;
    play_state.frame = 4;
  }

  int frame_ptr = dog_frames[play_state.frame];
  play_state.dog->attr2 = play_state.frame << 12 | frame_ptr;
}

void move(int y, int x, int next_y, int next_x) {
  if (y <= (HEIGHT - 32) && next_y > (HEIGHT - 32)) {
    play_state.dy = 0;
    play_state.y = (HEIGHT - 32);
  } else {
    play_state.y = next_y;
  }
  play_state.x = next_x;
  UNUSED(x);
}
