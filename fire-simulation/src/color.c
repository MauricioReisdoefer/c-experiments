#include <stdio.h>
#include "color.h"

Color FireIntensityToColor(int intensity)
{
    static Color table[10] = {
        {0, 0, 0, 255},      // 0
        {40, 0, 0, 255},     // 1
        {80, 0, 0, 255},     // 2
        {120, 10, 0, 255},   // 3
        {160, 30, 0, 255},   // 4
        {200, 60, 0, 255},   // 5
        {230, 100, 0, 255},  // 6
        {255, 150, 0, 255},  // 7
        {255, 200, 50, 255}, // 8
        {255, 255, 180, 255} // 9
    };

    if (intensity < 0)
        intensity = 0;
    if (intensity > 9)
        intensity = 9;

    return table[intensity];
}
