#include "collision.h"

#define platform1_floor 40
#define platform1_left 30
#define platform1_right 90

//Right side of screen lowest
#define platform2_floor 50
#define platform2_left 100
#define platform2_right WIDTH

//Right side of screen, 2nd from bottom
#define platform3_floor 70
#define platform3_left 175
#define platform3_right WIDTH

#define platform4_floor 60
#define platform4_left 50
#define platform4_right 95

#define platform5_floor 100
#define platform5_left 130
#define platform5_right 172

//Short platform half-way up the right
#define platform6_floor 125
#define platform6_left 180
#define platform6_right 210

//Short platform half-way up the right
#define platform7_floor 120
#define platform7_left 90
#define platform7_right 120

/*
  0
  0
  0
  0
  dy
  dx
  y
  x
*/
u8 left_wall(struct point *start, struct point *end, struct object *obj);
u8 left_wall(struct point *start, struct point *end, struct object *obj) {
  if (start->x >= 0 && end->x < 0) {
    obj->dx = 0;
    obj->loc.x = 0;
    return (1) | (1 << 2); // dx and x were set 00001010
  }
  return 0; // Nothing was set
}

u8 right_wall(struct point *start, struct point *end, struct object *obj);
u8 right_wall(struct point *start, struct point *end, struct object *obj) {
  if (start->x <= (WIDTH - 32) && end->x > (WIDTH - 32)) {
    obj->dx = 0;
    obj->loc.x = (WIDTH - 32);
    return (1) | (1 << 2); // dx and x were set 00001010
  }
  return 0; // Nothing was set
}

u8 death_box(struct point *start, struct point *end, struct object *obj);
u8 death_box(struct point *start, struct point *end, struct object *obj) {
  if (start->y <= (HEIGHT - 32) && end->y > (HEIGHT - 32)) {
      obj->health = 0;
  }
  return 0;
}

u8 ceiling(struct point *start, struct point *end, struct object *obj);
u8 ceiling(struct point *start, struct point *end, struct object *obj) {
  if (start->y >= 0 && end->y < 0) {
      obj->dy = 0;
      obj->loc.y = 0;
      return (1 << 1) | (1 << 3);
  }
  return 0;
}

inline u8 platform(struct point *start, struct point *end, struct object *obj,
                   int left, int right, int floor);
inline u8 platform(struct point *start, struct point *end, struct object *obj,
                   int left, int right, int floor) {
  if (start->x >= left && start->x <= right && start->y <= (HEIGHT - floor) &&
      end->y > (HEIGHT - floor)) {
    obj->dy = 0;
    obj->loc.y = (HEIGHT - floor);
    return (1 << 1) | (1 << 3); // dy and y were set 00001010
  }
  return 0; // Nothing was set
}

u8 platform_1(struct point *start, struct point *end, struct object *obj);
u8 platform_1(struct point *start, struct point *end, struct object *obj) {
  return platform(start, end, obj, platform1_left, platform1_right,
                  platform1_floor);
}

u8 platform_2(struct point *start, struct point *end, struct object *obj);
u8 platform_2(struct point *start, struct point *end, struct object *obj) {
  return platform(start, end, obj, platform2_left, platform2_right,
                  platform2_floor);
}

u8 platform_3(struct point *start, struct point *end, struct object *obj);
u8 platform_3(struct point *start, struct point *end, struct object *obj) {
  return platform(start, end, obj, platform3_left, platform3_right,
                  platform3_floor);
}

u8 platform_4(struct point *start, struct point *end, struct object *obj);
u8 platform_4(struct point *start, struct point *end, struct object *obj) {
  return platform(start, end, obj, platform4_left, platform4_right,
                  platform4_floor);
}

u8 platform_5(struct point *start, struct point *end, struct object *obj);
u8 platform_5(struct point *start, struct point *end, struct object *obj) {
  return platform(start, end, obj, platform5_left, platform5_right,
                  platform5_floor);
}

u8 platform_6(struct point *start, struct point *end, struct object *obj);
u8 platform_6(struct point *start, struct point *end, struct object *obj) {
  return platform(start, end, obj, platform6_left, platform6_right,
                  platform6_floor);
}

u8 platform_7(struct point *start, struct point *end, struct object *obj);
u8 platform_7(struct point *start, struct point *end, struct object *obj) {
  return platform(start, end, obj, platform7_left, platform7_right,
                  platform7_floor);
}

/*
struct collision {
    collision_action *action;
    struct point start;
    struct point end;
};
*/
int collision_size = 11;
struct collision collisions[] = {
    {left_wall, {0, 0}, {1, 1}},
    {right_wall, {0, 0}, {1, 1}},
    {ceiling, {0, 0}, {1, 1}},
    {death_box, {0, 0}, {1, 1}},
    {platform_1,
     {platform1_left + 32 - 5, (HEIGHT - platform1_floor + 32)},
     {platform1_right + 16 - 5, (HEIGHT + platform1_floor - 32)}},
    {platform_2,
     {platform2_left + 32 - 5, (HEIGHT - platform2_floor + 32)},
     {platform2_right, (HEIGHT + platform2_floor - 32)}},
    {platform_3,
     {platform3_left + 32 - 5, (HEIGHT - platform3_floor + 32)},
     {platform3_right, (HEIGHT + platform3_floor - 32)}},
    {platform_4,
     {platform4_left + 32 - 5, (HEIGHT - platform4_floor + 32)},
     {platform4_right + 16 - 5, (HEIGHT + platform4_floor - 32)}},
    {platform_5,
     {platform5_left + 32 - 5, (HEIGHT - platform5_floor + 32)},
     {platform5_right + 16 - 5, (HEIGHT + platform5_floor - 32)}},
    {platform_6,
     {platform6_left + 32 - 5, (HEIGHT - platform6_floor + 32)},
     {platform6_right + 16 - 5, (HEIGHT + platform6_floor - 32)}},
    {platform_7,
     {platform7_left + 32 - 5, (HEIGHT - platform7_floor + 32)},
     {platform7_right + 16 - 5, (HEIGHT + platform7_floor - 32)}},
};
