
// X PAUSES
// Z UNPAUSES
// LEFT CLICK TO CREATE / KILL CELL

#define SDL_MAIN_HANDLED // Tell SDL to use main function

#include <SDL2/SDL.h>
#include <stdio.h>


#define WHITE 0xffffffff // Color White
#define BLACK 0x00000000 // Color Black
#define GREEN 0x1fe04c   // Color Green

#define WINDOW_WIDTH 1720
#define WINDOW_HEIGHT 1000

#define CELL_WIDTH 15
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

void logic(SDL_Surface *surface, int columns, int rows)
{
    // Temporary array to store the next generation of cells
    int next_state[rows][columns];

    // Loop over all cells in the grid
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            // Count live neighbors
            int live_neighbors = 0;
            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    if (dx == 0 && dy == 0)
                        continue; // Skip the current cell itself

                    int nx = x + dx;
                    int ny = y + dy;

                    // Check for out-of-bounds
                    if (nx >= 0 && nx < columns && ny >= 0 && ny < rows)
                    {
                        if (cell_states[ny][nx] == ALIVE)
                        {
                            live_neighbors++;
                        }
                    }
                }
            }

            // Apply the Game of Life rules
            if (cell_states[y][x] == ALIVE)
            {
                // Cell survives if it has 2 or 3 live neighbors
                if (live_neighbors < 2 || live_neighbors > 3)
                    next_state[y][x] = DEAD;
                else
                    next_state[y][x] = ALIVE;
            }
            else
            {
                // Cell becomes alive if it has exactly 3 live neighbors
                if (live_neighbors == 3)
                    next_state[y][x] = ALIVE;
                else
                    next_state[y][x] = DEAD;
            }
        }
    }

    // Now copy the next state back into the original grid and redraw
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            // Update the cell state
            cell_states[y][x] = next_state[y][x];
            // Redraw the cell based on its new state
            draw_cell(surface, x, y, cell_states[y][x]);
        }
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
    int time_stop = 0;


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
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_x)
                {
                    time_stop = 1;
                }
                if(event.key.keysym.sym == SDLK_z)
                {
                    time_stop = 0;
                }
                
            }
        }

        if(!time_stop)
        {
        // Update the grid to the next generation
        logic(surface, columns, rows);
        SDL_UpdateWindowSurface(window);
        // Delay to control the speed of the simulation 
        SDL_Delay(100);
        }
    }

    // Clean up SDL resources
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

