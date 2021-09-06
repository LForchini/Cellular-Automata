#pragma once

#include "include/engine/engine.h"

#define WIDTH 640
#define HEIGHT 480

#define CELL_WIDTH 10
#define X_CELLS (WIDTH / CELL_WIDTH)
#define Y_CELLS (HEIGHT / CELL_WIDTH)

#define NEIGHBOUR_COMPLETE 1
#define NEIGHBOUR_ORTHOGONAL 2

typedef struct cell_t
{
    int state;
    int next_state;
} Cell;

typedef struct colour_t
{
    int r;
    int g;
    int b;
} Colour;

typedef struct memory_t
{
    Cell ***cells;
    int updating;
} Memory;

int *get_cell_neighbour_states(Engine *engine, int x, int y, int mode);
Colour logic_game_of_life(Engine *engine, int x, int y);