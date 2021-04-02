#include "play_screen.h"

struct play play_state;

void initialize_play_screen(void) {
  struct play state = {shadow, 0, 0, 5};
  play_state = state;
}

void draw_play_screen(void) {
  int flip_horizontal = 1 << 12;
  int y = 0;
  int x = 0;

  play_state.dog->attr0 = y | DOG_PALETTE_TYPE | DOG_SPRITE_SHAPE;
  play_state.dog->attr1 = x | DOG_SPRITE_SIZE | flip_horizontal;
  play_state.dog->attr2 = DOG0_PALETTE_ID | dog_frames[play_state.frame];

  if (play_state.delay > play_state.frame_delay) {
    play_state.delay = 0;
    play_state.frame = (play_state.frame + 1) % DOG_FRAMES;
  }
  (play_state.delay)++;

  int frame_ptr = dog_frames[play_state.frame];
  play_state.dog->attr2 = DOG0_PALETTE_ID | frame_ptr;
}
