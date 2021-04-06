#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>

#include "gba.h"

#include "images/ghost.h"
#include "images/dog.h"
#include "images/night.h"

void draw_welcome_screen(void);
void initialize_screen(void);

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
