#include "graphics.h"
#include "background.h"
#include "foreground.h"
#include "window.h"

Pair calc_arena_grid_size(Pair window_size, const int GRID_WIDTH, const int WALL_WIDTH)
{
    Pair grid_size;
    grid_size.x = (window_size.x - 2 * WALL_WIDTH) / GRID_WIDTH;
    grid_size.y = (window_size.y - 2 * WALL_WIDTH) / GRID_WIDTH;
    return grid_size;
}

void main(void)
{   
    srand(time(NULL));

    const int GRID_WIDTH = 50;
    const int WALL_WIDTH = 5;

    const Pair WINDOW_SIZE = 
    {
        .x = (rand() % (1001 -  5 * GRID_WIDTH - 2 * WALL_WIDTH)) + 5 * GRID_WIDTH + 2 * WALL_WIDTH,
        .y = (rand() % (701 - 5 * GRID_WIDTH - 2 * WALL_WIDTH)) + 5 * GRID_WIDTH + 2 * WALL_WIDTH
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