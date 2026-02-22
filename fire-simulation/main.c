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
    int result = Max(0, current - rand() % 2);
    return result;
}

int matrix[60][102];
int HEIGHT = 60;
int WIDTH = 102;

typedef struct
{
    unsigned char r, g, b, a;
} Color;

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

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return -1;
    }
    SDL_Window *window = SDL_CreateWindow("Fire Animation", WIDTH * 10, HEIGHT * 10, SDL_WINDOW_RESIZABLE);
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
    Uint64 lastTime = SDL_GetTicks();
    int frameCount = 0;
    float fps = 0.0f;
    while (z)
    {
        Uint64 currentTime = SDL_GetTicks();
        frameCount++;

        if (currentTime - lastTime >= 1000)
        {
            fps = frameCount / ((currentTime - lastTime) / 1000.0f);
            frameCount = 0;
            lastTime = currentTime;

            char title[64];
            snprintf(title, sizeof(title), "Fire Animation - FPS: %.2f", fps);
            SDL_SetWindowTitle(window, title);
        }

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
