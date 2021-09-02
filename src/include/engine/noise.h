#pragma once

double lerp(double a, double b, double w)
{
    return (1 - w) * a + w * b;
}

double noise_1D(double x);
double noise_2D(double x, double y);
double noise_3D(double x, double y, double z);