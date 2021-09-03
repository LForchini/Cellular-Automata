#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>

#define ENGINE_PXM_ENABLE 1
#define ENGINE_PXM_DISABLE 0

typedef struct memory_t Memory;

typedef struct engine_t
{
    int running;
    SDL_Window *window;
    SDL_Renderer *renderer;

    int pixel_mode;
    SDL_Texture *texture;
    unsigned char *pixels;
    int pitch;

    int width;
    int height;
    Memory *memory;

    Uint32 previous_time;
    Uint32 delta;
    int framerate;
    int frame_time;
} Engine;

#include "include/engine/draw.h"
#include "include/engine/utils.h"

void engine_handle_events(Engine *, SDL_Event *);
void engine_on_frame(Engine *);

Engine *engine_create(char *title, int width, int height, int pixel_mode)
{
    Engine *engine = (Engine *)malloc(sizeof(Engine));
    memset(engine, 0, sizeof(Engine));
    SDL_Init(SDL_INIT_EVERYTHING);
    engine->running = 1;
    engine->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    engine->renderer = SDL_CreateRenderer(engine->window, -1, 0);
    if (pixel_mode)
        engine->texture = SDL_CreateTexture(engine->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    engine->width = width;
    engine->height = height;
    engine->pixel_mode = pixel_mode;

    seed_random();

    return engine;
}

void engine_destroy(Engine *engine)
{
    SDL_DestroyWindow(engine->window);
    SDL_DestroyRenderer(engine->renderer);
    if (engine->pixel_mode)
        SDL_DestroyTexture(engine->texture);
    SDL_Quit();
    free(engine);
}

void engine_draw_frame(Engine *engine)
{
    if (engine->pixel_mode)
        SDL_RenderCopy(engine->renderer, engine->texture, NULL, NULL);
    SDL_RenderPresent(engine->renderer);
}

void engine_run(Engine *engine)
{
    SDL_Event e;
    engine->previous_time = SDL_GetTicks();
    while (engine->running)
    {
        while (SDL_PollEvent(&e))
            engine_handle_events(engine, &e);

        engine->delta = SDL_GetTicks() - engine->previous_time;
        engine->previous_time = SDL_GetTicks();

        if (engine->pixel_mode)
            SDL_LockTexture(engine->texture, NULL, (void **)&engine->pixels, &engine->pitch);
        engine_on_frame(engine);
        if (engine->pixel_mode)
            SDL_UnlockTexture(engine->texture);
        engine_draw_frame(engine);

        if (engine->framerate)
        {
            int delay = engine->frame_time - (SDL_GetTicks() % engine->frame_time);
            SDL_Delay(delay);
        }
    }
}

void engine_set_framerate(Engine *engine, int fr)
{
    engine->framerate = fr;
    engine->frame_time = 1000 / fr;
}