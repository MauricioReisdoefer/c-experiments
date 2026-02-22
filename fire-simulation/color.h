#pragma once

typedef struct
{
    unsigned char r, g, b, a;
} Color;

Color FireIntensityToColor(int intensity);
