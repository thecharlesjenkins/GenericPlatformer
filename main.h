#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>

#include "gba.h"

#include "images/ghost.h"
#include "images/dog.h"
#include "images/night.h"
#include "collision.h"
#include "play_screen.h"

void draw_welcome_screen(void);
void initialize_screen(void);
void draw_lose_screen(void);
void reset_screen(void);

struct object default_dog = {.sprite = shadow, .loc = {50, 150}, .dy = 10, .dx = 0, .facing = 1, .health = 100, .lives = 3, .points = 0};
struct play default_state = {0, 0, 5};

int gravity = -1;
/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

#endif
