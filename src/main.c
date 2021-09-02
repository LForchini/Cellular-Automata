#include "main.h"

#include <stdlib.h>

int main()
{
    Engine *engine = engine_create("Cellular Automata", WIDTH, HEIGHT, ENGINE_PXM_ENABLE);
    engine->memory = (Memory *)malloc(sizeof(Memory));

    engine->memory->cells = (Cell **)malloc(sizeof(Cell *) * WIDTH * HEIGHT);
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        Cell *c = (Cell *)malloc(sizeof(Cell));
        c->state = i % 2;
        c->next_state = 0;
        engine->memory->cells[i] = c;
    }

    engine_run(engine);
    engine_destroy(engine);
    return 0;
}

void engine_handle_events(Engine *engine, SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        engine->running = 0;
        break;
    default:
        break;
    }
}

void engine_on_frame(Engine *engine)
{
    for (int i = 0; i < engine->width * engine->height; i++)
    {
        Cell *c = engine->memory->cells[i];
        int x = i % engine->width, y = i / engine->width;

        if (c->state == 1)
        {
            engine_set_pixel(engine, x, y, 0, 0, 0);
        }
        else
        {
            engine_set_pixel(engine, x, y, 255, 255, 255);
        }
    }
}