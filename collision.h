#ifndef COLLISION_H
#define COLLISION_H

#include "gba.h"

#define platform1_floor 40
#define platform1_left 30
#define platform1_right 90

// Right side of screen lowest
#define platform2_floor 50
#define platform2_left 100
#define platform2_right WIDTH

// Right side of screen, 2nd from bottom
#define platform3_floor 70
#define platform3_left 175
#define platform3_right WIDTH

// Medium platform in middle of screen, slightly left
#define platform4_floor 100
#define platform4_left 50
#define platform4_right 95

// Medium platform to right of middle of screen
#define platform5_floor 100
#define platform5_left 130
#define platform5_right 172

// Short platform half-way up the right
#define platform6_floor 125
#define platform6_left 180
#define platform6_right 210

// Short platform at middle top
#define platform7_floor 120
#define platform7_left 90
#define platform7_right 120

// Platform on the left bottom
#define platform8_floor 55
#define platform8_left -10
#define platform8_right 30

// Platform on the left, second from bottom
#define platform9_floor 70
#define platform9_left 5
#define platform9_right 50

#define exit_x 95
#define exit_y 110

#define coin1_x 20
#define coin1_y 125

#define coin2_x 209
#define coin2_y 55

#define coin3_x 118
#define coin3_y 15

struct point {
  int x;
  int y;
};

struct coin_obj {
  struct point pos;
  int visible;
  int visible_last_frame;
};

struct object {
  OamEntry *sprite;
  struct point loc;
  int dy;
  int dx;
  int facing;
  int health;
  int lives;
  int points;
};

u8 coin_func(struct coin_obj *a_coin, struct point *end, struct object *obj);

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

  Set bit to 1 to notify caller that the respective field was set by the
  collision action Caller then knows which fields it needs to modify to prevent
  overwriting collision method
*/

typedef u8(collision_action)(struct point *start, struct point *end,
                             struct object *);

struct collision {
  collision_action *action;
  struct point start;
  struct point end;
};

#endif
