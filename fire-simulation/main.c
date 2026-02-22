#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <SDL3/SDL.h>

int Max(int min, int value)
{
    if (min < value)
        return value;
    return min;
}

int GetNextLayer(int current)
{
    int result = Max(0, current - rand() % 3);
    return result;
}

int matrix[15][30];
int HEIGHT = 15;
int WIDTH = 30;

typedef struct
{
    unsigned char r, g, b, a;
} Color;

Color FireIntensityToColor(int intensity)
{
    if (intensity < 0)
        intensity = 0;
    if (intensity > 9)
        intensity = 9;

    Color c = {0, 0, 0, 255};

    if (intensity == 0)
        return c;

    float t = intensity / 9.0f;

    c.r = (unsigned char)(255 * t);
    c.g = (unsigned char)(200 * (t * t));
    c.b = (unsigned char)(50 * (t * t * t));

    return c;
}

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return -1;
    }
    SDL_Window *window = SDL_CreateWindow("Fire Animation", 300, 150, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0)
            {
                matrix[i][j] = 9;
            }
            else
            {
                matrix[i][j] = GetNextLayer(matrix[i - 1][j]);
            }
        }
    }

    int z = 1;
    while (z)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        for (int i = HEIGHT - 1; i >= 0; i--)
        {
            for (int j = WIDTH - 1; j >= 0; j--)
            {
                if (i > 0)
                {
                    matrix[i][j] = GetNextLayer(matrix[i - 1][j]);
                }
                SDL_FRect rect;
                rect.x = j * 10;
                rect.y = i * 10;

                rect.w = 10;
                rect.h = 10;

                Color cor = FireIntensityToColor(matrix[i][j]);

                SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
}
