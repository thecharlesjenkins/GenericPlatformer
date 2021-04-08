#include "play_screen.h"
#include "images/coin.h"
#include "images/night.h"
#include <stdio.h>

int draw_play_screen(u32 previousButtons, u32 currentButtons,
                     struct object *dog, struct play *state) {
  char lives[10];
  sprintf(lives, "Lives: %d", dog->lives);

  char points[11];
  sprintf(points, "Points: %d", dog->points);
  drawString(17, 10, points, 0x0fd0); // A nice green

  if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
    dog->facing = 0;
    dog->dx = 1;
  } else if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
    dog->facing = 1;
    dog->dx = -1;
  } else {
    dog->dx = 0;
  }

  if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons) &&
      dog->dy == 0) {
    dog->dy = 10;
  }

  dog->dy += gravity;
  struct point next_pos = {dog->loc.x - dog->dx, dog->loc.y - dog->dy};

  u8 pos_bitmask = 0;
  for (int i = 0; i < collision_size; i++) {
    pos_bitmask |= (*collisions[i].action)(&dog->loc, &next_pos, dog);
    drawRectDMA(collisions[i].start.y, collisions[i].start.x,
                collisions[i].end.x - collisions[i].start.x, 2, WHITE);
  }

  for (int i = 0; i < coins_size; i++) {
    u8 coin_result = coin_func(&coins[i], &next_pos, dog);
    if (coin_result) {
      drawImageDMA(coins[i].pos.y, coins[i].pos.x, COIN_WIDTH, COIN_HEIGHT,
                   night); //Undraw coins
      undrawString(17, 10, points, night);
    }
  }
  drawString(5, 10, lives, 0x0fd0); // A nice green

  if (dog->points == 3) {
    for (int i = 0; i < coins_size; i++) {
      coins[i].visible = 1;
    }
    return 2; // win game
  }

  if (dog->health <= 0) {
    if (dog->lives == 1) {
      for (int i = 0; i < coins_size; i++) {
        coins[i].visible = 1;
      }
      return 1; //lose game
    }
    undrawString(5, 10, lives, night);
    dog->lives--;
    dog->loc.x = 50;
    dog->loc.y = 150;
    dog->dy = 10;
    dog->dx = 0;
    dog->facing = 1;
    dog->health = 100;
  } else {
    if ((1 & pos_bitmask) == 0) {
      // x not changed
      dog->loc.x = next_pos.x;
    }
    if ((2 & pos_bitmask) == 0) {
      // y not changed
      dog->loc.y = next_pos.y;
    }
  }

  dog->sprite->attr0 = dog->loc.y | DOG_PALETTE_TYPE | DOG_SPRITE_SHAPE;
  dog->sprite->attr1 = dog->loc.x | DOG_SPRITE_SIZE | (dog->facing << 12);

  if (KEY_DOWN((BUTTON_LEFT | BUTTON_RIGHT), currentButtons)) {
    dog->sprite->attr2 = state->frame << 12 | dog_frames[state->frame];

    if (state->delay > state->frame_delay) {
      state->delay = 0;
      state->frame = (state->frame + 1) % DOG_FRAMES;
    }
    (state->delay)++;
  } else {
    state->delay = 0;
    state->frame = 4;
  }

  int frame_ptr = dog_frames[state->frame];
  dog->sprite->attr2 = state->frame << 12 | frame_ptr;

  return 0;
}
