#ifndef PLAY_SCREEN_H
#define PLAY_SCREEN_H

#include "gba.h"
#include "images/dog.h"

extern OamEntry shadow[128];

void initialize_play_screen(void);
void draw_play_screen(void);

struct play {
    OamEntry *dog;
    int delay;
    int frame;
    int frame_delay;
};

#endif
