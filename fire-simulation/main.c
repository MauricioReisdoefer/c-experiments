#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <SDL3/SDL.h>

#include "color.h"
#include "fire.h"

int matrix[60][102];
int HEIGHT = 40;
int WIDTH = 70;

int main(int argc, char *argv[])
{

    int maxFPS = 60;

    if (argc > 1)
    {
        maxFPS = atoi(argv[1]);
        if (maxFPS <= 0)
            maxFPS = 60;
    }

    Uint64 frameDelay = 1000 / maxFPS;

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
                rect.y = (HEIGHT - 1 - i) * 10;

                rect.w = 10;
                rect.h = 10;

                Color cor = FireIntensityToColor(matrix[i][j]);

                SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
        SDL_RenderPresent(renderer);
        Uint64 frameTime = SDL_GetTicks() - currentTime;

        if (frameTime < frameDelay)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    SDL_DestroyWindow(window);
}
