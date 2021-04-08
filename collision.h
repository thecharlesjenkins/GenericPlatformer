#ifndef COLLISION_H
#define COLLISION_H

#include "gba.h"

struct point {
    int x;
    int y;
};

struct object {
  OamEntry *sprite;
  struct point loc;
  int dy;
  int dx;
  int facing;
  int health;
  int lives;
};

/*
  Returns binary mask of template:
  0
  0
  0
  0
  dy
  dx
  y
  x

  Set bit to 1 to notify caller that the respective field was set by the collision action
  Caller then knows which fields it needs to modify to prevent overwriting collision method 
*/

typedef u8 (collision_action)(struct point *start, struct point *end, struct object *);

struct collision {
    collision_action *action;
    struct point start;
    struct point end;
};

#endif
