#include "graphics.h"
#include "background.h"

Pair calc_arena_pixel_size(const Arena ARENA)
{
    Pair pixel_size;
    pixel_size.x = ARENA.GRID_WIDTH * ARENA.GRID_SIZE.x;
    pixel_size.y = ARENA.GRID_WIDTH * ARENA.GRID_SIZE.y;
    return pixel_size;
}

void draw_wall(const Arena ARENA, const Pair ARENA_PIXEL_SIZE)
{
    setColour(red);
    fillRect(0, 0, ARENA.WALL_WIDTH, ARENA_PIXEL_SIZE.y + 2 * ARENA.WALL_WIDTH);
    fillRect(0, 0, ARENA_PIXEL_SIZE.x + 2 * ARENA.WALL_WIDTH, ARENA.WALL_WIDTH);
    fillRect(0, ARENA.WALL_WIDTH + ARENA_PIXEL_SIZE.y, ARENA_PIXEL_SIZE.x + 2 * ARENA.WALL_WIDTH, ARENA.WALL_WIDTH);
    fillRect(ARENA.WALL_WIDTH + ARENA_PIXEL_SIZE.x, 0, ARENA.WALL_WIDTH, ARENA_PIXEL_SIZE.y + 2 * ARENA.WALL_WIDTH);
}

void draw_lines(const Arena ARENA, const Pair ARENA_PIXEL_SIZE)
{   
    setColour(black);
    int x = ARENA.WALL_WIDTH, y = ARENA.WALL_WIDTH;
    while (x <= ARENA.WALL_WIDTH + ARENA_PIXEL_SIZE.x)
    {
        drawLine(x, y, x, y + ARENA_PIXEL_SIZE.y);
        x += ARENA.GRID_WIDTH;
    }
    x = ARENA.WALL_WIDTH;
    while (y <= ARENA.WALL_WIDTH + ARENA_PIXEL_SIZE.y)
    {
        drawLine(x, y, x + ARENA_PIXEL_SIZE.x, y);
        y += ARENA.GRID_WIDTH;
    }
}

void draw_background(const const Arena ARENA)
{  
    background();
    clear();
    setLineWidth(1);

    const Pair ARENA_PIXEL_SIZE = calc_arena_pixel_size(ARENA);

    draw_wall(ARENA, ARENA_PIXEL_SIZE);
    draw_lines(ARENA, ARENA_PIXEL_SIZE);
}
