#define SDL_MAIN_HANDLED // Tell SDL to use main function

#include <SDL2/SDL.h>
#include <stdio.h>

#define WHITE 0xffffffff // Color White
#define BLACK 0x00000000 // Color Black
#define GREEN 0x1fe04c   // Color Green

#define WINDOW_WIDTH 1720
#define WINDOW_HEIGHT 1000

#define CELL_WIDTH 30
#define LINE_WIDTH 2

#define ALIVE 1
#define DEAD 0

// Cell states array (0: dead, 1: alive)
int cell_states[WINDOW_HEIGHT / CELL_WIDTH][WINDOW_WIDTH / CELL_WIDTH];

// Function to draw the grid
void draw_grid(SDL_Surface *surface, int columns, int rows)
{
    for (int i = 0; i <= rows; i++)
    {
        SDL_Rect row_line = {0, i * CELL_WIDTH, WINDOW_WIDTH, LINE_WIDTH};
        SDL_FillRect(surface, &row_line, GREEN);
    }
    for (int i = 0; i <= columns; i++)
    {
        SDL_Rect col_line = {i * CELL_WIDTH, 0, LINE_WIDTH, WINDOW_HEIGHT};
        SDL_FillRect(surface, &col_line, GREEN);
    }
}

// Function to draw a single cell
void draw_cell(SDL_Surface *surface, int cell_x, int cell_y, int state)
{
    int pixel_x = cell_x * CELL_WIDTH;
    int pixel_y = cell_y * CELL_WIDTH;

    SDL_Rect cell_rect = {pixel_x + LINE_WIDTH, pixel_y + LINE_WIDTH, CELL_WIDTH - LINE_WIDTH, CELL_WIDTH - LINE_WIDTH};

    if (state == ALIVE)
        SDL_FillRect(surface, &cell_rect, WHITE);
    else
        SDL_FillRect(surface, &cell_rect, BLACK);
}

// Function to toggle the cell state between alive and dead
void toggle_cell(SDL_Surface *surface, int cell_x, int cell_y)
{
    if (cell_states[cell_y][cell_x] == DEAD)
    {
        cell_states[cell_y][cell_x] = ALIVE;
        draw_cell(surface, cell_x, cell_y, ALIVE);
    }
    else
    {
        cell_states[cell_y][cell_x] = DEAD;
        draw_cell(surface, cell_x, cell_y, DEAD);
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;

    char *window_title = "Game of Life";

    int columns = WINDOW_WIDTH / CELL_WIDTH;
    int rows = WINDOW_HEIGHT / CELL_WIDTH;

    // Initialize all cells to DEAD
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            cell_states[i][j] = DEAD;

            

    SDL_Window *window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    // Draw the initial grid and update the surface
    draw_grid(surface, columns, rows);
    SDL_UpdateWindowSurface(window);

    int exit_flag = 0;

    while (!exit_flag)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit_flag = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    int cell_x = mouse_x / CELL_WIDTH;
                    int cell_y = mouse_y / CELL_WIDTH;

                    // Toggle cell state
                    toggle_cell(surface, cell_x, cell_y);

                    // Update the window surface to display the changes
                    SDL_UpdateWindowSurface(window);
                }
            }
        }
    }

    // Clean up SDL resources
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
