
#include "main.h"

void draw_scan_line(int y, int x0, int x1, char symbol, char grid[HEIGHT][WIDTH])
{
   int left = min(x0, x1);
   int right = max(x0, x1);

   for (int x = left; x <= right; ++x)
        grid[y][x] = symbol;
}

void draw_flat_bottom(vec2 t, vec2 b0, vec2 b1, char grid[HEIGHT][WIDTH])
{
    int xb = t.x;
    int xe = t.x;

    float x_dec0 = (t.x - b0.x) / (b0.y - t.y);
    float x_dec1 = (t.x - b1.x) / (b1.y - t.y);
        
    int yb = (int)t.y;
    int ye = (int)b0.y + 1;

    for (int y = yb; y < ye; ++y)
    {
        draw_scan_line(y, (int)xb, (int)xe, '*', grid);
        xb -= x_dec0;
        xe -= x_dec1;
    }
}

void draw_flat_top(vec2 t0, vec2 t1, vec2 b, char grid[HEIGHT][WIDTH])
{
    int xb = t0.x;
    int xe = t1.x;

    float x_inc0 = (b.x - t0.x) / (b.y - t0.y);
    float x_inc1 = (b.x - t1.x) / (b.y - t1.y);
        
    int yb = (int)t0.y;
    int ye = (int)b.y + 1;

    for (int y = yb; y < ye; ++y)
    {
        draw_scan_line(y, (int)xb, (int)xe, '*', grid);
        xb += x_inc0;
        xe += x_inc1;
    }
}

void draw_triangle(vec2 vector0, vec2 vector1, vec2 vector2, char grid[HEIGHT][WIDTH])
{
    vec2 v0 = vector0;
    vec2 v1 = vector1;
    vec2 v2 = vector2;

    // sort by asc y
    if (v0.y > v1.y)
    {
        v0 = vector1;
        v1 = vector0;
    }
    
    if (v1.y > v2.y)
    {
        vec2 tmp = v2;
        v2 = v1;
        v1 = tmp;
    }

    if (v0.y > v1.y)
    {
        vec2 tmp = v0;
        v0 = v1;
        v1 = tmp;
    }

    if (v2.y == v1.y)
    {
        draw_flat_bottom(v0, v1, v2, grid);
        return;
    }

    if (v0.y == v1.y)
    {
        draw_flat_top(v0, v1, v2, grid);
        return;
    }

    vec2 midpoint = 
    {
        v0.x + (v2.x - v0.x) * (v1.y - v0.y) / (v2.y - v0.y),
        v1.y
    };
    
    draw_flat_bottom(v0, v1, midpoint, grid);
    draw_flat_top(v1, midpoint, v2, grid);
}

void draw_cube()
{
    for (int i = 0; i < 12; ++i)
    {
        int triangle[3];
        for (int j = 0; j < 3; ++j)
            triangle[j] = cube_triangles[i][j];

        vec3 transformed_vertices[3];
        for (int k = 0; k < 3; ++k)
        {
            transformed_vertices[k] = cube_vertices[triangle[k]];
            // rotate
            // push to screen
            // scale
        }
        // triangle displayed ?
        // back face culling
        // continue early
        // project 2D Point
            // 
        // draw triangle
    }
}

void render(char grid[HEIGHT][WIDTH], char* buffer)
{
    // clear_screen();
    printf("\x1B[H");
    for (int i = 0; i < HEIGHT; ++i)
    {
        // fuer jede reihe 
        int start_offset = i * (WIDTH + 1); // buffer begin offset per row

        // slice
        for (int j = 0; j < WIDTH; ++j)
            buffer[start_offset+j] = grid[i][j];
        buffer[start_offset + WIDTH] = '\n';
    }

    for (int i = 0; i < BUFFER_SIZE; ++i)
        putchar(buffer[i]);
}

void init(char grid[HEIGHT][WIDTH])
{
    printf("\x1B[2J\x1B[?25l");  // clear screen + hide cursor
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            grid[y][x] = ' ';
}

int main()
{ 
    char grid[HEIGHT][WIDTH];
    char buffer[BUFFER_SIZE];
    init(grid);

    while(1)
    {
        vec2 v1 = {10, 5};
        vec2 v2 = {150, 15};
        vec2 v3 = {70, 34};

        vec2 v4 = {200, 5};
        vec2 v5 = {10, 5};
        vec2 v6 = {100, 30};
        
        // draw_flat_bottom(v1, v2, v3, grid);
        // draw_flat_top(v4, v5, v6, grid);
        draw_triangle(v1, v2, v3, grid);
        render(grid, buffer);
        usleep(100000);
    }
    
    return 0;
}

