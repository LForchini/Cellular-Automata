#pragma once

#include <math.h>
#include <stdlib.h>

typedef struct vector2d_t
{
    double x;
    double y;
} Vector2D;

Vector2D *vector2d_new(double x, double y)
{
    Vector2D *v = (Vector2D *)malloc(sizeof(Vector2D));
    v->x = x;
    v->y = y;
    return v;
}

Vector2D *vector2d_fromAngle(double a)
{
    Vector2D *v = (Vector2D *)malloc(sizeof(Vector2D));
    v->x = cos(a);
    v->y = sin(a);
    return v;
}

double vector2d_dotProduct(Vector2D *v1, Vector2D *v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}

void vector2d_destroy(Vector2D *v)
{
    free(v);
}