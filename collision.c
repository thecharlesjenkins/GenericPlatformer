#include "collision.h"

#define platform1_floor 40
#define platform1_left 30
#define platform1_right 90

#define platform2_floor 50
#define platform2_left 100
#define platform2_right WIDTH

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

u8 platform_1(struct point *start, struct point *end, struct object *obj);
u8 platform_1(struct point *start, struct point *end, struct object *obj) {
  if (start->x >= platform1_left && start->x <= platform1_right && start->y <= (HEIGHT - platform1_floor) &&
      end->y > (HEIGHT - platform1_floor)) {
    obj->dy = 0;
    obj->loc.y = (HEIGHT - platform1_floor);
    return (1 << 1) | (1 << 3); // dy and y were set 00001010
  }
  return 0; // Nothing was set
}

u8 platform_2(struct point *start, struct point *end, struct object *obj);
u8 platform_2(struct point *start, struct point *end, struct object *obj) {
  if (start->x >= platform2_left && start->x <= platform2_right && start->y <= (HEIGHT - platform1_floor) &&
      end->y > (HEIGHT - platform2_floor)) {
    obj->dy = 0;
    obj->loc.y = (HEIGHT - platform2_floor);
    return (1 << 1) | (1 << 3); // dy and y were set 00001010
  }
  return 0; // Nothing was set
}

/*
struct collision {
    collision_action *action;
    struct point start;
    struct point end;
};
*/
int collision_size = 4;
struct collision collisions[] = {
    {left_wall, {0, 0}, {0, 0}},
    {right_wall, {0, 0}, {0, 0}}, 
    {platform_1, {platform1_left + 32 - 5, (HEIGHT - platform1_floor + 32)}, {platform1_right + 16 - 5, (HEIGHT + platform1_floor - 32)}},
    {platform_2, {platform2_left + 32 - 5, (HEIGHT - platform2_floor + 32)}, {platform2_right, (HEIGHT + platform2_floor - 32)}},
};
