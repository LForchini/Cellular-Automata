#pragma once

#include "include/engine/engine.h"

#define WIDTH 640
#define HEIGHT 480

typedef struct cell_t
{
    int state;
    int next_state;
} Cell;

typedef struct memory_t
{
    Cell **cells;
} Memory;