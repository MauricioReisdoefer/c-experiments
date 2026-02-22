#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

typedef struct Vector2
{
    int x;
    int y;
} Vector2;

int HEIGHT = 15;
int WIDTH = 30;

int Max(int min, int value)
{
    if (min < value)
        return value;
    return min;
}

int matrix[15][30];

int main()
{

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == HEIGHT - 1)
            {
                matrix[i][j] = 9;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
    int z = 1;

    while (z)
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                printf("%d", matrix[i][j]);
            }
            printf("\n");
        }
        Sleep(1000);
        system("cls");
    }
}

int GetNextLayer(int current)
{
    int result = current * rand() % 3;
    return result;
}
