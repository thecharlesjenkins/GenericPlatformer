#ifndef PLAY_SCREEN_H
#define PLAY_SCREEN_H

#include "gba.h"
#include "images/dog.h"
#include "collision.h"

extern OamEntry shadow[128];
extern int gravity;
extern u32 vBlankCounter;

void initialize_play_screen(void);
void draw_play_screen(u32, u32);
void move(int y, int x, int next_y, int next_x);

typedef struct play {
  OamEntry *dog;
  int delay;
  int frame;
  int frame_delay;
  int facing;
  int x;
  int y;
  int dy;
  int dx;
} play;

#endif
