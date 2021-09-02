#pragma once

#include <time.h>
#include <stdlib.h>

void seed_random()
{
    srand(time(0));
}