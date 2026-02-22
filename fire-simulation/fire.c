#include <stdio.h>
#include <stdlib.h>
#include "fire.h"

int Max(int min, int value)
{
    if (min < value)
        return value;
    return min;
}

int GetNextLayer(int current)
{
    int result = Max(0, current - rand() % 2);
    return result;
}