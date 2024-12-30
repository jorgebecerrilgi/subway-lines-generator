#include <SDL2/SDL.h>
#include <iostream>
#include "Vector2.hpp"
#include "Grid.hpp"

const int WIN_WIDTH = 720;
const int WIN_HEIGHT = 400;
const int GRID_WIDTH = 368;
const int GRID_HEIGHT = 208;
const int GRID_STEP = 16;
const SDL_Color GRID_COLOR = {210, 210, 210, 255};

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO != 0))
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
        "Subway Lines Generator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH,
        WIN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Draw the background white.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw grid on the center of the screen.
    Vector2<int> GRID_ORIGIN = {(WIN_WIDTH - GRID_WIDTH) / 2, (WIN_HEIGHT - GRID_HEIGHT) / 2};
    Grid grid(GRID_ORIGIN, GRID_WIDTH, GRID_HEIGHT, GRID_STEP);
    grid.draw(renderer, GRID_COLOR);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        SDL_WaitEvent(&e);
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
