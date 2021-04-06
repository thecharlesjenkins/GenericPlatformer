#ifndef COLLISION_H
#define COLLISION_H

#include "play_screen.h"

struct point {
    int x;
    int y;
};

typedef int (*collision_func)(struct point *start, struct point *end);

typedef int (*collision_action)(int *play_object);

struct collision {
    collision_func *func;
    collision_action *action;
    struct point start;
    struct point end;
};

#endif
