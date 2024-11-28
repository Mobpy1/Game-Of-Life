#define SDL_MAIN_HANDLED // Tell SDL to use main function

#include <SDL2/SDL.h>
#include <stdio.h>



#define WHITE 0xffffffff   // Color White
#define BLACK 0x00000000   // Color Black
#define PINK 0xfc028b      // Color Pink
#define GREEN 0x1fe04c     // Color Green
#define TURQUOISE 0x05ffff // Color Turquoise

#define WINDOW_WIDTH 1720
#define WINDOW_HEIGHT 1000

#define CELL_WIDTH 30
#define LINE_WIDTH 2





void draw_grid(SDL_Surface* surface ,int columns , int rows)
{
    for (int i=0; i<rows+1 ; i++)
    {
        SDL_Rect row_line = { 0 , i * CELL_WIDTH, WINDOW_WIDTH , 1 };

        SDL_FillRect(surface , &row_line , GREEN);
    }
    for (int i=0; i<columns+1 ; i++)
    {
        SDL_Rect col_line = { i * CELL_WIDTH, 0 , 1, WINDOW_HEIGHT };

        SDL_FillRect(surface, &col_line , GREEN);
    }
}

void draw_cell(SDL_Surface* surface , int cell_x , int cell_y)
{
    int pixel_x = cell_x * CELL_WIDTH;
    int pixel_y = cell_y * CELL_WIDTH;
    
    SDL_Rect cell_rect = {pixel_x,pixel_y,CELL_WIDTH,CELL_WIDTH};
    SDL_FillRect(surface, &cell_rect, WHITE);
}









int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;

    char *window_title = "Game of Life";    
    
    int columns = WINDOW_WIDTH / CELL_WIDTH;
    int rows = WINDOW_HEIGHT / CELL_WIDTH;

    SDL_Window *window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    draw_grid(surface  ,  columns  ,  rows);
    

    // Update the window surface to display the rectangle

    int exit_flag = 0;

    while(!exit_flag)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit_flag = 1;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    int mouse_x = event.button.x;
                    int mouse_y = event.button.y;

                    int cell_x = mouse_x / CELL_WIDTH;
                    int cell_y = mouse_y / CELL_WIDTH;

                    draw_cell(surface, cell_x, cell_y);

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
