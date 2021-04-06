#include "play_screen.h"

// int surfaces[][] = {{}};
void draw_play_screen(u32 previousButtons, u32 currentButtons) {
  static object dog = {shadow, 50, 150, 10, 0, 1, 100};
  static play state = {0, 0, 5};

  if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
    dog.facing = 0;
    dog.dx = 1;
  } else if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
    dog.facing = 1;
    dog.dx = -1;
  } else {
    dog.dx = 0;
  }

  if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons) && dog.dy == 0) {
    dog.dy = 10;
  }

  dog.dy += gravity;
  int next_loc_y = dog.y - dog.dy;
  int next_loc_x = dog.x - dog.dx;

  move(&dog, dog.y, dog.x, next_loc_y, next_loc_x);

  dog.sprite->attr0 = dog.y | DOG_PALETTE_TYPE | DOG_SPRITE_SHAPE;
  dog.sprite->attr1 =
      dog.x | DOG_SPRITE_SIZE | (dog.facing << 12);

  if (KEY_DOWN((BUTTON_LEFT | BUTTON_RIGHT), currentButtons)) {
    dog.sprite->attr2 =
        state.frame << 12 | dog_frames[state.frame];

    if (state.delay > state.frame_delay) {
      state.delay = 0;
      state.frame = (state.frame + 1) % DOG_FRAMES;
    }
    (state.delay)++;
  } else {
    state.delay = 0;
    state.frame = 4;
  }

  int frame_ptr = dog_frames[state.frame];
  dog.sprite->attr2 =state.frame << 12 | frame_ptr;
}

void move(object *obj, int y, int x, int next_y, int next_x) {
  if (y <= (HEIGHT - 32) && next_y > (HEIGHT - 32)) {
    obj->dy = 0;
    obj->y = (HEIGHT - 32);
  } else {
    obj->y = next_y;
  }
  obj->x = next_x;
  UNUSED(x);
}
