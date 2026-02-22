#include <stdio.h>
#include <SDL3/SDL.h>

#include "color.h"
#include "fire.h"

#define CELL_SIZE 10

static const int HEIGHT = 40;
static const int WIDTH = 70;

static int matrix[60][102];

void InitMatrix(void)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0)
                matrix[i][j] = 9;
            else
                matrix[i][j] = GetNextLayer(matrix[i - 1][j]);
        }
    }
}

void UpdateMatrix(void)
{
    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        for (int j = WIDTH - 1; j >= 0; j--)
        {
            if (i > 0)
                matrix[i][j] = GetNextLayer(matrix[i - 1][j]);
        }
    }
}

void RenderMatrix(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        for (int j = WIDTH - 1; j >= 0; j--)
        {
            SDL_FRect rect = {
                .x = j * CELL_SIZE,
                .y = (HEIGHT - 1 - i) * CELL_SIZE,
                .w = CELL_SIZE,
                .h = CELL_SIZE};

            Color cor = FireIntensityToColor(matrix[i][j]);
            SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}

void UpdateFPS(SDL_Window *window,
               Uint64 *lastTime,
               int *frameCount)
{
    Uint64 currentTime = SDL_GetTicks();
    (*frameCount)++;

    if (currentTime - *lastTime >= 1000)
    {
        float fps = *frameCount / ((currentTime - *lastTime) / 1000.0f);

        char title[64];
        snprintf(title, sizeof(title),
                 "Fire Animation - FPS: %.2f", fps);

        SDL_SetWindowTitle(window, title);

        *frameCount = 0;
        *lastTime = currentTime;
    }
}

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

    SDL_Window *window =
        SDL_CreateWindow("Fire Animation",
                         WIDTH * CELL_SIZE,
                         HEIGHT * CELL_SIZE,
                         SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, NULL);

    InitMatrix();

    int running = 1;
    Uint64 lastTime = SDL_GetTicks();
    int frameCount = 0;

    while (running)
    {
        Uint64 frameStart = SDL_GetTicks();

        UpdateFPS(window, &lastTime, &frameCount);
        UpdateMatrix();
        RenderMatrix(renderer);

        Uint64 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay)
            SDL_Delay(frameDelay - frameTime);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}