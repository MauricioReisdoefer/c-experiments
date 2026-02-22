#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

typedef struct Vector2
{
    int x;
    int y;
} Vector2;

int main()
{
    printf("main");
    Sleep(3000);
    system("cls");
    printf("main 2");
}

Vector2 GetNextLayer(Vector2 current)
{
    Vector2 result = (Vector2){current.x * rand() % 3, current.y * rand() % 3};
    result.x = Max(0, result.x);
    result.y = Max(0, result.y);
    return result;
}

int Max(int min, int value)
{
    if (min < value)
        return value;
    return min;
}