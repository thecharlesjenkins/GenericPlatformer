#include "play_screen.h"

void draw_play_screen(u32 previousButtons, u32 currentButtons) {
  static struct object dog = {shadow, {50, 150}, 10, 0, 1, 100};
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

  if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons) &&
      dog.dy == 0) {
    dog.dy = 10;
  }

  dog.dy += gravity;
  struct point next_pos = {dog.loc.x - dog.dx, dog.loc.y - dog.dy};

  u8 pos_bitmask = 0;
  for (int i = 0; i < collision_size; i++) {
    pos_bitmask |= (*collisions[i].action)(&dog.loc, &next_pos, &dog);
  }
  drawRectDMA(collisions[3].start.y, collisions[3].start.x, collisions[3].end.x - collisions[3].start.x, 1, WHITE);
  drawRectDMA(collisions[2].start.y, collisions[2].start.x, collisions[2].end.x - collisions[2].start.x, 1, WHITE);

  if ((1 & pos_bitmask) == 0) {
    // x not changed
    dog.loc.x = next_pos.x;
  }
  if ((2 & pos_bitmask) == 0) {
    // y not changed
    dog.loc.y = next_pos.y;
  }

  dog.sprite->attr0 = dog.loc.y | DOG_PALETTE_TYPE | DOG_SPRITE_SHAPE;
  dog.sprite->attr1 = dog.loc.x | DOG_SPRITE_SIZE | (dog.facing << 12);

  setPixel(dog.loc.y, dog.loc.x, WHITE);

  if (KEY_DOWN((BUTTON_LEFT | BUTTON_RIGHT), currentButtons)) {
    dog.sprite->attr2 = state.frame << 12 | dog_frames[state.frame];

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
  dog.sprite->attr2 = state.frame << 12 | frame_ptr;
}
