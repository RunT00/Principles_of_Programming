#ifndef WINDOW_H
#define WINDOW_H
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct
{
    int x;
    int y;
} Pair;


typedef struct
{
    Pair GRID_SIZE;
    int GRID_WIDTH;
    int WALL_WIDTH;
} Arena;

#endif
