#include "graphics.h"
#include "foreground.h"
#include "robot.h"

Pair grid_to_pixel(Pair grid_coord, const Arena ARENA)
{
    Pair pixel_coord;
    pixel_coord.x = grid_coord.x * ARENA.GRID_WIDTH + ARENA.WALL_WIDTH;
    pixel_coord.y = grid_coord.y * ARENA.GRID_WIDTH + ARENA.WALL_WIDTH;
    return pixel_coord;
}

Pair rand_grid_coord(Pair grid_size)
{   
    Pair grid_coord;
    grid_coord.x = rand() % grid_size.x;
    grid_coord.y = rand() % grid_size.y;
    return grid_coord;
}

// Load temp array that only stores three points to be connected for drawing a robot
void load_temp(Pair pixel_coord, enum direction direction, int grid_dots[][8], int temp_grids[][3])
{   
    int positions[3];
    switch (direction)
    {
        case LEFT: positions[0] = 1; positions[1] = 4; positions[2] = 6; break;
        case UP: positions[0] = 3; positions[1] = 6; positions[2] = 0; break;
        case RIGHT: positions[0] = 5; positions[1] = 0; positions[2] = 2; break;
        case DOWN: positions[0] = 7; positions[1] = 2; positions[2] = 4; break;
    }
   
    for (size_t i = 0; i < 3; i++)
    {
        temp_grids[0][i] = pixel_coord.x + grid_dots[0][positions[i]];
        temp_grids[1][i] = pixel_coord.y + grid_dots[1][positions[i]];
    }
}

int min(int x, int y)
{
    if (x <= y)
    {
        return x;
    }
    return y;
}

int calc_mid(int x)
{
    if (x % 2 == 0)
    {
        return (x / 2 - 1);
    }
    return (x / 2);
}

int check_marker_exists(const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x], Pair pos_marker)
{
    if (arr_arena[pos_marker.y][pos_marker.x] == 'M')
    {
        return 1;
    }
    return 0;
}

void init_grids(const int GRID_WIDTH, int grid_dots[][8])
{   
    /* for drawing triangular robot, intialize 8 points in a grid like
    * - * - *
    - - - - -
    * - - - *
    - - - - -
    S - * - *
    and choose 3 points for each direction of robot,
    starting from S clockwisely,
    there will be interval outside these 5x5 points in a grid */

    int interval = (int)(GRID_WIDTH / 10.0);
    int offset = (int)((GRID_WIDTH - 2 * interval) / 2.0);

    grid_dots[0][0] = grid_dots[0][1] = grid_dots[0][2] = interval;
    grid_dots[0][3] = grid_dots[0][7] = interval + offset;
    grid_dots[0][4] = grid_dots[0][5] = grid_dots[0][6] =  interval + 2 * offset;

    grid_dots[1][2] = grid_dots[1][3] = grid_dots[1][4] = interval;
    grid_dots[1][1] = grid_dots[1][5] = interval + offset;
    grid_dots[1][0] = grid_dots[1][6] = grid_dots[1][7] =  interval + 2 * offset;
}

void init_arr(const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x])
{
    for (size_t i = 0; i < ARENA.GRID_SIZE.y; i++)
    {
        for (size_t j = 0; j < ARENA.GRID_SIZE.x; j++)
        {
            arr_arena[i][j] = ' ';
        } 
    }
}

// Generate obstacles to form circular area in the middle
void init_obstacles(const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x])
{
    int radius = rand() % (min(ARENA.GRID_SIZE.x, ARENA.GRID_SIZE.y) / 2);
    if (radius < 2)
    {
        radius = 2;
    }
    
    Pair centre = {.x = calc_mid(ARENA.GRID_SIZE.x), .y = calc_mid(ARENA.GRID_SIZE.y)};
    for (int i = 0; i < ARENA.GRID_SIZE.y; i++)
    {
        for (int j = 0; j < ARENA.GRID_SIZE.x; j++)
        {
            if ((centre.y - i) * (centre.y - i) + (centre.x - j) * (centre.x - j) > radius * radius + 1)
            {
                arr_arena[i][j] = 'O';
            }
        }
    }
}

Pair init_pos_robot(const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x])
{   
    Pair pos_robot = rand_grid_coord(ARENA.GRID_SIZE);
    while (arr_arena[pos_robot.y][pos_robot.x] != ' ')
    {
        pos_robot = rand_grid_coord(ARENA.GRID_SIZE);
    }
    return pos_robot;
}

void init_markers(const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x], int num_markers)
{
    size_t i = 0;
    while (i < num_markers)
    { 
        Pair pos_marker = rand_grid_coord(ARENA.GRID_SIZE);
        if (check_marker_exists(ARENA, arr_arena, pos_marker) == 0 && arr_arena[pos_marker.y][pos_marker.x] == ' ')
        {
            arr_arena[pos_marker.y][pos_marker.x] = 'M';
            i += 1;
        }
    }
}

void draw_objects(const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x])
{
    for (size_t i = 0; i < ARENA.GRID_SIZE.y; i++)
    {   
        for (size_t j = 0; j < ARENA.GRID_SIZE.x; j++)
        {
            if (arr_arena[i][j] == 'M')
            {   
                setColour(gray);
                Pair grid_coord = {j, i};
                Pair pixel_coord = grid_to_pixel(grid_coord, ARENA);
                int interval = ARENA.GRID_WIDTH / 10;
                fillOval(pixel_coord.x + interval + 1, pixel_coord.y + interval + 1, ARENA.GRID_WIDTH - 2 * interval - 1, ARENA.GRID_WIDTH - 2 * interval - 1);
            }
            else if (arr_arena[i][j] == 'O')
            {   
                setColour(black);
                Pair grid_coord = {j, i};
                Pair pixel_coord = grid_to_pixel(grid_coord, ARENA);
                int interval = ARENA.GRID_WIDTH / 50;
                fillRect(pixel_coord.x + interval + 1, pixel_coord.y + interval + 1, ARENA.GRID_WIDTH - 2 * interval - 1, ARENA.GRID_WIDTH - 2 * interval - 1);
            }
        }
    }
}

void draw_robot(Robot *ptr_robot, const Arena ARENA, int grid_dots[][8], int temp_grids[][3])
{
    int interval = ARENA.GRID_WIDTH / 10;
    Pair pixel_coord = grid_to_pixel(ptr_robot->grid_coord, ARENA);
    load_temp(pixel_coord, ptr_robot->direction, grid_dots, temp_grids);

    setColour(blue);
    fillPolygon(3, temp_grids[0], temp_grids[1]);

    setColour(red);
    drawLine(temp_grids[0][1], temp_grids[1][1], temp_grids[0][2], temp_grids[1][2]);
}

// Breadth-first search to check if all the markers are reachable, nobody blocked by any obstacle
int check_reachable(Pair start_pos, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x], int num_markers)
{   
    int visited[MAX_Y][MAX_X] = {0};
    visited[start_pos.y][start_pos.x] = 1;

    Pair queue[ARENA.GRID_SIZE.x * ARENA.GRID_SIZE.y];
    int head = 0, tail = 0;
    queue[tail++] = start_pos;

    int count = 0;
    
    while(head < tail)
    {
        Pair current_pos = queue[head++];
        Robot temp_robot = {.grid_coord = current_pos, .direction = 0};
        if (atMarker(&temp_robot, ARENA, arr_arena))
        {
            count++;
        }

        if (count == num_markers)
        {
            return 1;
        }

        for (size_t i = 0; i < 4; i++)
        {
            if (canMoveForward(&temp_robot, ARENA, arr_arena))
            {
                forward(&temp_robot);
                if (!visited[temp_robot.grid_coord.y][temp_robot.grid_coord.x])
                {
                    visited[temp_robot.grid_coord.y][temp_robot.grid_coord.x] = 1;
                    queue[tail++] = temp_robot.grid_coord;
                }
                temp_robot.grid_coord = current_pos;
            }
            right(&temp_robot);
        }
    }
    if (count != num_markers)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Depth-first search to use a dummy robot to find the path and store it, but not drawn on the window
int find_path(Robot *temp_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x],Pair path[MAX_PATH_LEN], int step, int visited[][ARENA.GRID_SIZE.x], int *path_len) 
{       
    if (visited[temp_robot->grid_coord.y][temp_robot->grid_coord.x] == 1)
    {
        return 0;
    }
    visited[temp_robot->grid_coord.y][temp_robot->grid_coord.x] = 1;

    path[step] = temp_robot->grid_coord;
    *path_len += 1;

    if (atMarker(temp_robot, ARENA, arr_arena))
    {   
        return 1;
    }
    int dir = temp_robot->direction;
    for (int i = 0; i < 4; i++)
    {
        if (canMoveForward(temp_robot, ARENA, arr_arena))
        {
            forward(temp_robot);
            if (find_path(temp_robot, ARENA, arr_arena, path, step+1, visited, path_len))
            {   
                return 1;
            }
            left(temp_robot);
            left(temp_robot);
            forward(temp_robot);
            left(temp_robot);
            left(temp_robot);
        }
        right(temp_robot);
    }
    temp_robot->direction = dir;
    return 0;
}

void draw_foreground(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x], int grid_dots[][8], int temp_grids[][3])
{
    clear();
    draw_objects(ARENA, arr_arena);
    draw_robot(ptr_robot, ARENA, grid_dots, temp_grids);
    sleep(50);
}

void run_foreground(Robot *ptr_robot, const Arena ARENA, char arr_arena[][ARENA.GRID_SIZE.x], int grid_dots[][8], int temp_grids[][3], int num_markers)
{
    draw_foreground(ptr_robot, ARENA, arr_arena, grid_dots, temp_grids);

    while(ptr_robot->num_carry < num_markers)
    {   
        Pair path[MAX_PATH_LEN];
        int path_len = 0;
        int visited[MAX_Y][MAX_X] = {0};
        Robot temp_robot = {.grid_coord = ptr_robot->grid_coord, .direction = ptr_robot->direction};

        find_path(&temp_robot, ARENA, arr_arena, path, 0, visited, &path_len);
        for (size_t i = 0; i < path_len; i++)
        {
            Pair current_pos = path[i];
            Pair next_pos = path[i + 1];

            int dx = next_pos.x - current_pos.x;
            int dy = next_pos.y - current_pos.y;
            int target_dir;

            if (dx == 1 && dy == 0)
            {
                target_dir = RIGHT;
            }
            else if (dx == -1 && dy == 0)
            {
                target_dir = LEFT;
            } 
            else if (dx == 0 && dy == -1)
            {
                target_dir = UP;
            } 
            else if (dx == 0 && dy == 1)
            {
                target_dir = DOWN;
            }  
            else
            {
                continue;
            }

            while (ptr_robot->direction != target_dir)
            {
                left(ptr_robot);
                draw_foreground(ptr_robot, ARENA, arr_arena, grid_dots, temp_grids);
            }
            
            if (canMoveForward(ptr_robot, ARENA, arr_arena))
            {
                forward(ptr_robot);
            }

            if (atMarker(ptr_robot, ARENA, arr_arena))
            {
                pickUpMarker(ptr_robot, ARENA, arr_arena);
            }

            draw_foreground(ptr_robot, ARENA, arr_arena, grid_dots, temp_grids);

            if (ptr_robot->num_carry == num_markers)
            {
                return;
            }
        }
    }

}

void init_foreground(const Arena ARENA)
{   
    foreground();
    clear();
    setLineWidth(1);

    int grid_dots[2][8];
    int temp_grids[2][3];
    init_grids(ARENA.GRID_WIDTH, grid_dots);

    char arr_arena[ARENA.GRID_SIZE.y][ARENA.GRID_SIZE.x]; // ' ' = empty, 'M' = marker, 'O' = obstacle
    int num_markers = rand() % 9 + 2;
    
    Robot robot;

    do
    {   
        init_arr(ARENA, arr_arena);
        init_obstacles(ARENA, arr_arena);
        init_markers(ARENA, arr_arena, num_markers);
        
        robot.grid_coord = init_pos_robot(ARENA, arr_arena);
        robot.direction = rand() % 4;
        robot.num_carry = 0;
    } 
    while (!check_reachable(robot.grid_coord, ARENA, arr_arena, num_markers));

    run_foreground(&robot, ARENA, arr_arena, grid_dots, temp_grids, num_markers);
}
