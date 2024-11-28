#define SDL_MAIN_HANDLED // Tell SDL to use main function

#include <SDL2/SDL.h>
#include <stdio.h>



#define WHITE 0xffffffff   // Color White
#define BLACK 0x00000000   // Color Black
#define PINK 0xfc028b      // Color Pink
#define GREEN 0x1fe04c     // Color Green
#define TURQUOISE 0x05ffff // Color Turquoise

#define width 1720
#define height 1000

#define active_life {30, 40, 10, 10}




void draw_grid(SDL_Surface* surface , int cell_width , int columns , int rows)
{
    for (int i=0; i<rows; i++)
    {
        SDL_Rect row_line = {0 ,i*cell_width, width ,1};

        SDL_FillRect(surface , &row_line, GREEN);
    }
    for (int i=0; i<columns; i++)
    {
        SDL_Rect col_line = {i*cell_width, 0 , 1, width };

        SDL_FillRect(surface, &col_line , GREEN);
    }
}

void draw_cell(SDL_Surface* surface , int cell_x , int cell_y)
{
    printf("no");
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    char *window_title = "Game of Life";
    
    int cell_width = 10;
    int columns = width / cell_width;
    int rows = height / cell_width;

    int cell_x = 10;
    int cell_y = 60;


    SDL_Window *window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_Rect life ={30, 40, 10, 10};
    

    draw_grid(surface , cell_width, columns,rows);
    draw_cell(surface, cell_x , cell_y);
    
    //SDL_FillRect(surface, &life, WHITE);

    // Update the window surface to display the rectangle
    SDL_UpdateWindowSurface(window);

    
    SDL_Delay(5000);

    // Clean up SDL resources
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
