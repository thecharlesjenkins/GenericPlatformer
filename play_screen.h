#ifndef PLAY_SCREEN_H
#define PLAY_SCREEN_H

#include "gba.h"
#include "images/dog.h"
#include "collision.h"

extern OamEntry shadow[128];
extern int gravity;
extern u32 vBlankCounter;

void draw_play_screen(u32, u32);

typedef struct play {
  int delay;
  int frame;
  int frame_delay;
} play;

typedef struct object {
  OamEntry *sprite;
  int x;
  int y;
  int dy;
  int dx;
  int facing;
  int health;
} object;

void move(object *obj, int y, int x, int next_y, int next_x);

#endif
