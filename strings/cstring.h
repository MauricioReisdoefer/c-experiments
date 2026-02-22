#pragma once

#include <stdio.h>

typedef struct String
{
    char *data;
    size_t lenght;
    size_t capacity;
} String;