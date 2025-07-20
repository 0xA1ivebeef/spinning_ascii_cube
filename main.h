
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 250
#define HEIGHT 60
#define ASPECT_RATIO 1.6f
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)
#define BUFFER_SIZE (HEIGHT * WIDTH+1)

#define min(a, b) ((a) > (b) ? (b) : (a))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct
{
    float x;
    float y;
} vec2;


typedef struct
{
    float x;
    float y;
    float z;
} vec3;

vec3 cube_vertices[8] = 
{
    {-1, -1, -1}, // 0 - 7
    {-1,  1, -1},
    { 1,  1, -1},
    { 1, -1, -1},
    { 1,  1,  1},
    { 1, -1,  1},
    {-1, -1,  1},
    {-1,  1,  1}
};

int cube_triangles[12][3] = 
{
    // front face
    {0, 1, 2},
    {0, 2, 3},
    
    // right
    {3, 2, 4},
    {3, 4, 5},
    
    // back
    {5, 4, 7},
    {5, 7, 6},
    
    // left
    {6, 7, 1},
    {6, 1, 0},
    
    // top
    {6, 0, 3},
    {6, 3, 5},
    
    // bottom
    {1, 7, 4},
    {1, 4, 2}
};

void clear_screen()
{
    printf("\033[2J\033[H");
}

