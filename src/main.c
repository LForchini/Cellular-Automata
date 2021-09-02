#include "main.h"

#include <stdlib.h>

int main()
{
    Engine *engine = engine_create("SDL Template", 640, 480);
    engine->memory = (Memory *)malloc(sizeof(Memory));

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
}
