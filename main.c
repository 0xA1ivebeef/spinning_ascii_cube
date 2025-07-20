
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

float A, B, C; 

float cube_width = 10;
int width = 160, height = 44;
float z_buffer[160 * 44];
char buffer[160 * 44];
int BACKGROUND_ASCII_CODE = ' ';
int distance_from_cam = 40;
float K1 = 40;
int idx;

float increment_speed = 0.6;

float x, y, z;
float ooz;
int xp, yp;

float calculate_x(int i, int j, int k)
{
    return  j * sin(A) * sin(B) * cos(C)  - k * cos(A) * sin(B) * cos(C) +
            j * cos(A) * sin(C)  + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculate_y(int i, int j, int k)
{
    return  j * cos(A) * cos(C) + k * sin(A) * cos(C) - 
            j * sin(A) * sin(B)  * sin(C) + k * cos(A) * sin(B)  * sin(C) -
            i * cos(B) * sin(C);
}

float calculate_z(int i, int j, int k)
{
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculate_for_surface(float cube_x, float cube_y, float cube_z, int ch)
{
    x = calculate_x(cube_x, cube_y, cube_z);
    y = calculate_y(cube_x, cube_y, cube_z);
    z = calculate_z(cube_x, cube_y, cube_z) + distance_from_cam;

    ooz = 1/z;

    xp = (int)(width/2 + K1 * ooz * x * 2);
    yp = (int)(height/2 + K1 * ooz * y);

    idx = xp + yp * width;
    if (idx >= 0 && idx < width * height)
    {
        if (ooz > z_buffer[idx])
        {
            z_buffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main()
{
    printf("\x1b[2J");
    while (1)
    {
        printf("\x1b[2J");
        memset(buffer, BACKGROUND_ASCII_CODE, width * height);
        memset(z_buffer, 0, width * height * 4);
        for (float cube_x = -cube_width; cube_x < cube_width; cube_x += increment_speed)
            for (float cube_y = -cube_width; cube_y < cube_width; cube_y += increment_speed)
            {
                calculate_for_surface(cube_x, cube_y, -cube_width, '~');
                calculate_for_surface(cube_width, cube_y, cube_x, '+');
                calculate_for_surface(-cube_width, cube_y, -cube_x, '-');
                calculate_for_surface(-cube_x, cube_y, cube_width, ':');
                calculate_for_surface(cube_x, -cube_width, -cube_y, '.');
                calculate_for_surface(cube_x, cube_width, cube_y, ',');
                
            }   
        printf("\x1b[H");
        for (int k = 0; k < width * height; ++k)
            putchar(k % width ? buffer[k] : 10);

        A += 0.005;
        B += 0.005;
        usleep(5000);
    }
    return 0;
}

