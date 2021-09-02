#pragma once

#include "include/engine/engine.h"

void engine_draw_point(Engine *engine, int x, int y)
{
    SDL_RenderDrawPoint(engine->renderer, x, y);
}

void engine_draw_line(Engine *engine, int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(engine->renderer, x1, y1, x2, y2);
}

void engine_set_pixel(Engine *engine, int x, int y, int r, int g, int b)
{
    engine->pixels[4 * (x + engine->width * y)] = r;
    engine->pixels[4 * (x + engine->width * y) + 1] = g;
    engine->pixels[4 * (x + engine->width * y) + 2] = b;
    engine->pixels[4 * (x + engine->width * y) + 3] = 255;
}

void engine_fill_circle(Engine *engine, int x, int y, int r)
{
    int l;
    for (int z = 0; z < r; z++)
    {
        l = sqrt(r * r - (z * z));
        engine_draw_line(engine, x - l, y + z, x + l, y + z);
        engine_draw_line(engine, x - l, y - z, x + l, y - z);
    }
}

void engine_draw_circle(Engine *engine, int x, int y, int r)
{
    int l;
    for (int z = 0; z < r; z++)
    {
        l = sqrt(r * r - (z * z));
        engine_draw_point(engine, x - l, y + z);
        engine_draw_point(engine, x + l, y + z);
        engine_draw_point(engine, x - l, y - z);
        engine_draw_point(engine, x + l, y - z);
        engine_draw_point(engine, x - z, y + l);
        engine_draw_point(engine, x + z, y + l);
        engine_draw_point(engine, x - z, y - l);
        engine_draw_point(engine, x + z, y - l);
    }
}

void engine_set_colour(Engine *engine, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(engine->renderer, r, g, b, a);
}

void engine_set_grayscale_colour(Engine *engine, int gray)
{
    SDL_SetRenderDrawColor(engine->renderer, gray, gray, gray, 255);
}

void engine_clear(Engine *engine, int r, int g, int b)
{
    engine_set_colour(engine, r, g, b, 255);
    SDL_RenderClear(engine->renderer);
}