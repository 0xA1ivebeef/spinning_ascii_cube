
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define WIDTH 121
#define HEIGHT 61
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)
#define ASPECT_RATIO 1.6f

typedef struct
{
    float x;
    float y;
} vector2d;

void render(vector2d** v, int size)
{
    char grid[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            grid[y][x] = ' ';

    grid[CENTER_Y][CENTER_X] = '+';

    // vektor aus ursprung
    for (int i = 0; i < size; ++i)
    {
        int x = CENTER_X + (int)round(v[i]->x);
        int y = CENTER_Y + (int)round(v[i]->y / ASPECT_RATIO);

        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            grid[y][x] = '*';
    }

    system("clear");
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
            putchar(grid[y][x]);
        putchar('\n');
    }
}

int main()
{
    vector2d t = {25.0f, 10.0f}; 
    vector2d b1 = {10.0f, 25.0f};
    vector2d b2 = {40.0f, 25.0f};

    vector2d* v[3];
    
    v[0] = &t;
    v[1] = &b1;
    v[2] = &b2;

    render(v, 3);

    return 0;
}

