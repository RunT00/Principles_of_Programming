#include "graphics.h"
#include "background.h"
#include "foreground.h"
#include "window.h"

void to_odd(int *x)
{
    if (*x % 2 == 0)
    {
        *x -= 1;
    }
}

Pair calc_arena_grid_size(const Pair WINDOW_SIZE, const int GRID_WIDTH, const int WALL_WIDTH)
{
    Pair grid_size;
    grid_size.x = (WINDOW_SIZE.x - 2 * WALL_WIDTH) / GRID_WIDTH;
    grid_size.y = (WINDOW_SIZE.y - 2 * WALL_WIDTH) / GRID_WIDTH;

    to_odd(&grid_size.x);
    to_odd(&grid_size.y);

    return grid_size;
}

void main(void)
{   
    srand(time(NULL));

    const int GRID_WIDTH = 50;
    const int WALL_WIDTH = 5;

    int side = (rand() % (701 - 5 * GRID_WIDTH - 2 * WALL_WIDTH)) + 5 * GRID_WIDTH + 2 * WALL_WIDTH;

    const Pair WINDOW_SIZE = 
    {
        .x = side,
        .y = side
    };
    
    const Arena ARENA =
    {   
        .GRID_WIDTH = GRID_WIDTH,
        .WALL_WIDTH = WALL_WIDTH,
        .GRID_SIZE = calc_arena_grid_size(WINDOW_SIZE, GRID_WIDTH, WALL_WIDTH)
    };

    setWindowSize(WINDOW_SIZE.x, WINDOW_SIZE.y);
    draw_background(ARENA);
    init_foreground(ARENA);
}