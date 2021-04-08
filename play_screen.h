#ifndef PLAY_SCREEN_H
#define PLAY_SCREEN_H

#include "gba.h"
#include "images/dog.h"
#include "collision.h"

extern OamEntry shadow[128];
extern int gravity;
extern u32 vBlankCounter;
extern struct collision collisions[];
extern int collision_size;
extern struct coin_obj coins[];
extern int coins_size;


typedef struct play {
  int delay;
  int frame;
  int frame_delay;
} play;

int draw_play_screen(u32, u32, struct object *, struct play *);

#endif
