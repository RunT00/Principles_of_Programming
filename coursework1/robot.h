#ifndef ROBOT_H
#define ROBOT_H
#include "window.h"
#include "foreground.h"

void forward(Robot *ptr_robot);
void left(Robot *ptr_robot);
void right(Robot *ptr_robot);
int atMarker(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x]);
int canMoveForward(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x]);
void pickUpMarker(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x]);
void dropMarker(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x]);
int markerCount(Robot *ptr_robot);

#endif