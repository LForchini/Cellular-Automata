#include "main.h"

#include <stdlib.h>

int main()
{
    Engine *engine = engine_create("Cellular Automata", WIDTH, HEIGHT, ENGINE_PXM_ENABLE);
    engine->memory = (Memory *)malloc(sizeof(Memory));
    engine_set_framerate(engine, 5);

    engine->memory->cells = (Cell ***)malloc(sizeof(Cell **) * X_CELLS);
    for (int x = 0; x < X_CELLS; x++)
    {
        engine->memory->cells[x] = (Cell **)malloc(sizeof(Cell *) * Y_CELLS);
        for (int y = 0; y < Y_CELLS; y++)
        {
            Cell *c = (Cell *)malloc(sizeof(Cell));
            c->state = 0;
            c->next_state = 0;
            engine->memory->cells[x][y] = c;
        }
    }

    engine->memory->cells[2][0]->state = 1;
    engine->memory->cells[2][1]->state = 1;
    engine->memory->cells[2][2]->state = 1;
    engine->memory->cells[1][2]->state = 1;
    engine->memory->cells[0][1]->state = 1;

    engine->memory->updating = 0;

    engine_run(engine);
    engine_destroy(engine);
    return 0;
}

void engine_handle_events(Engine *engine, SDL_Event *event)
{
    SDL_KeyboardEvent *kbe;

    switch (event->type)
    {
    case SDL_QUIT:
        engine->running = 0;
        break;
    case SDL_KEYUP:
        kbe = (SDL_KeyboardEvent *)event;
        if (kbe->keysym.sym == SDLK_SPACE)
            engine->memory->updating = !engine->memory->updating;
        break;
    default:
        break;
    }
}

void engine_on_frame(Engine *engine)
{

    for (int y = 0; y < Y_CELLS; y++)
        for (int x = 0; x < X_CELLS; x++)
        {
            Colour c = logic_game_of_life(engine, x, y);

            for (int j = 0; j < CELL_WIDTH; j++)
                for (int i = 0; i < CELL_WIDTH; i++)
                    engine_set_pixel(engine, (CELL_WIDTH * x) + i, (CELL_WIDTH * y) + j, c.r, c.g, c.b);
        }

    if (engine->memory->updating)
        for (int y = 0; y < Y_CELLS; y++)
            for (int x = 0; x < X_CELLS; x++)
                engine->memory->cells[x][y]->state = engine->memory->cells[x][y]->next_state;
}

/* 
    Returns a list of states of neighbours. 
    NEIGHBOUR_COMPLETE mode means all 8 neighbours are added;
        NEIGHBOUR_ORTHOGANAL only orthoganally adjacent cells.
    The list is ordered from left to right, top to bottom.
*/
int *get_cell_neighbour_states(Engine *engine, int x, int y, int mode)
{
    Cell ***cells = engine->memory->cells;

    int length = 4;
    if (mode == NEIGHBOUR_COMPLETE)
        length = 8;
    int *neighbours = (int *)malloc(sizeof(int) * length);
    memset(neighbours, 0, length * sizeof(int));

    int i = 0;
    if (x > 0 && y > 0 && mode == NEIGHBOUR_COMPLETE)
        neighbours[i++] = cells[x - 1][y - 1]->state;
    if (y > 0)
        neighbours[i++] = cells[x][y - 1]->state;
    if (x < X_CELLS - 1 && y > 0 && mode == NEIGHBOUR_COMPLETE)
        neighbours[i++] = cells[x + 1][y - 1]->state;

    if (x > 0)
        neighbours[i++] = cells[x - 1][y]->state;
    if (x < X_CELLS - 1)
        neighbours[i++] = cells[x + 1][y]->state;

    if (x > 0 && y < Y_CELLS - 1 && mode == NEIGHBOUR_COMPLETE)
        neighbours[i++] = cells[x - 1][y + 1]->state;
    if (y < Y_CELLS - 1)
        neighbours[i++] = cells[x][y + 1]->state;
    if (x < X_CELLS - 1 && y < Y_CELLS - 1 && mode == NEIGHBOUR_COMPLETE)
        neighbours[i++] = cells[x + 1][y + 1]->state;

    return neighbours;
}

/* 
    Implements the logic for Conway's Game of Life
    There are two states, alive and dead:
        Alive:
            If there is 1 or 0 alive neighbours, die
            If there 4+ alive neighbours, die
        Dead:
            If there is 3 alive neighbours, live
*/
Colour logic_game_of_life(Engine *engine, int x, int y)
{
    Cell *c = engine->memory->cells[x][y];
    Colour colour;

    int *neighbour_states = get_cell_neighbour_states(engine, x, y, NEIGHBOUR_COMPLETE);
    int sum = 0;
    for (int i = 0; i < 8; i++)
        sum += neighbour_states[i];
    free(neighbour_states);

    if (c->state == 1)
    {
        colour.r = 255;
        colour.g = 255;
        colour.b = 255;

        if (sum <= 1)
            c->next_state = 0;
        else if (sum >= 4)
            c->next_state = 0;
        else
            c->next_state = 1;
    }
    else
    {
        colour.r = 0;
        colour.g = 0;
        colour.b = 0;

        if (sum == 3)
            c->next_state = 1;
        else
            c->next_state = 0;
    }

    return colour;
}