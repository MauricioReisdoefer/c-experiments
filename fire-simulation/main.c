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

int GetNextLayer(int current)
{
    int result = Max(0, current - rand() % 3);
    return result;
}

int matrix[15][30];

int main()
{

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
        for (int i = HEIGHT - 1; i >= 0; i--)
        {
            for (int j = WIDTH - 1; j >= 0; j--)
            {
                if (i > 0)
                {
                    matrix[i][j] = GetNextLayer(matrix[i - 1][j]);
                }
                printf("%d", matrix[i][j]);
            }
            printf("\n");
        }
        Sleep(1000);
        system("cls");
    }
}
