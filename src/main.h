#pragma once

#include "include/engine/engine.h"

#define WIDTH 640
#define HEIGHT 480

#define CELL_WIDTH 10
#define X_CELLS (WIDTH / CELL_WIDTH)
#define Y_CELLS (HEIGHT / CELL_WIDTH)

#define NM_8 1
#define NM_4 2

#define NEIGHBOUR_MODE NM_8

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
} Memory;

int *get_cell_neighbour_states(Engine *engine, int x, int y);
Colour logic_game_of_life(Engine *engine, int x, int y);