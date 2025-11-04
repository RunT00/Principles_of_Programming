#include "foreground.h"
#include "robot.h"

void forward(Robot *ptr_robot)
{
    switch(ptr_robot->direction)
    {
        case LEFT: ptr_robot->grid_coord.x -= 1; break;
        case RIGHT: ptr_robot->grid_coord.x += 1; break;
        case UP: ptr_robot->grid_coord.y -= 1; break;
        case DOWN: ptr_robot->grid_coord.y += 1; break;
    }
}

void left(Robot *ptr_robot)
{
    ptr_robot->direction = (ptr_robot->direction + 3) % 4;
}

void right(Robot *ptr_robot)
{
    ptr_robot->direction = (ptr_robot->direction + 5) % 4;
}

int atMarker(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x])
{   
    for (size_t i = 0; i < ARENA.GRID_SIZE.y; i++)
    {
        for (size_t j = 0; j < ARENA.GRID_SIZE.x; j++)
        {
            if (arr_arena[i][j] == 'M' && i == ptr_robot->grid_coord.y && j == ptr_robot->grid_coord.x)
            {
                return 1;
            }
        }
    }
    return 0;
}

int canMoveForward(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x])
{
    switch(ptr_robot->direction)
    {
        case LEFT: 
            if (ptr_robot->grid_coord.x <= 0)
            {
                return 0;
            }
            else if (arr_arena[ptr_robot->grid_coord.y][ptr_robot->grid_coord.x - 1] == 'O')
            {
                return 0;
            }
            break;
        case RIGHT:
            if (ptr_robot->grid_coord.x >= ARENA.GRID_SIZE.x - 1)
            {
                return 0;
            }
            else if (arr_arena[ptr_robot->grid_coord.y][ptr_robot->grid_coord.x + 1] == 'O')
            {
                return 0;
            }
            break;
        case UP:
            if (ptr_robot->grid_coord.y <= 0)
            {
                return 0;
            }
            else if (arr_arena[ptr_robot->grid_coord.y - 1][ptr_robot->grid_coord.x] == 'O')
            {
                return 0;
            }
            break;
        case DOWN:
            if (ptr_robot->grid_coord.y >= ARENA.GRID_SIZE.y - 1)
            {
                return 0;
            }
            else if (arr_arena[ptr_robot->grid_coord.y + 1][ptr_robot->grid_coord.x] == 'O')
            {
                return 0;
            }
            break;
    }
    return 1;
}

void pickUpMarker(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x])
{   
    arr_arena[ptr_robot->grid_coord.y][ptr_robot->grid_coord.x] = ' ';
    ptr_robot->num_carry += 1;
}

void dropMarker(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x])
{
    arr_arena[ptr_robot->grid_coord.y][ptr_robot->grid_coord.x] = 'M';
    ptr_robot->num_carry = 0;
}

int markerCount(Robot *ptr_robot)
{   
    return ptr_robot->num_carry;
}
