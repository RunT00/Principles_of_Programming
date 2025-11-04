#ifndef FOREGROUND_H
#define FOREGROUND_H
#include "window.h"

enum direction {LEFT, UP, RIGHT, DOWN};

#define MAX_PATH_LEN 400
#define MAX_Y 20
#define MAX_X 20

typedef struct
{
    Pair grid_coord;
    enum direction direction;
    int num_carry;
} Robot;

void init_foreground(const Arena ARENA);

#endif