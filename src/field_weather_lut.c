#include "global.h"
#include "field_weather_lut.h"

const u8 gDarkenedContrastColorMaps[NUM_WEATHER_COLOR_MAPS][32] = 
{
    {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
    {0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 11, 12, 13, 14, 14, 15, 16, 17, 18, 19, 20, 21, 21, 22, 23, 24, 25, 26, 27},
    {0, 0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 11, 12, 13, 13, 14, 15, 16, 17, 17, 18, 19, 20, 21, 21, 22, 23, 24, 25},
    {0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 11, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 19, 20, 20, 21, 22, 23, 24, 24, 25},
    {1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 12, 13, 13, 14, 15, 15, 16, 17, 18, 18, 19, 20, 20, 21, 22, 23, 23, 24, 25, 25},
    {1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9, 10, 13, 14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 20, 21, 22, 22, 23, 24, 24, 25, 26},
    {1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9, 10, 15, 15, 16, 16, 17, 18, 18, 19, 19, 20, 21, 21, 22, 22, 23, 24, 24, 25, 26, 26},
    {1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9, 10, 16, 16, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 23, 23, 24, 24, 25, 25, 26, 27},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 19, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 20, 20, 21, 21, 22, 22, 22, 23, 23, 24, 24, 24, 25, 25, 26, 26, 26, 27, 27, 28},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 21, 22, 22, 22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 27, 27, 27, 28, 28},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 28, 28, 28},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 25, 25, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 29, 29, 29},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    {1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}
};

const u8 gContrastColorMaps[NUM_WEATHER_COLOR_MAPS][32] =
{
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 11, 14, 15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 24, 25, 26, 27, 28, 29, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 16, 17, 18, 18, 19, 20, 21, 22, 22, 23, 24, 25, 26, 26, 27, 28, 29, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 17, 18, 19, 19, 20, 21, 22, 22, 23, 24, 25, 25, 26, 27, 28, 28, 29, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 17, 18, 19, 20, 20, 21, 22, 22, 23, 24, 24, 25, 26, 26, 27, 28, 28, 29, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 19, 19, 20, 21, 21, 22, 22, 23, 24, 24, 25, 26, 26, 27, 27, 28, 29, 29, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 20, 20, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 27, 27, 28, 28, 29, 29, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 22, 23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 27, 28, 28, 29, 29, 30, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 23, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 27, 27, 27, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31}
};