#include <SDL2/SDL.h>
#include <iostream>

void drawGrid(SDL_Renderer *renderer, int x1, int y1, int w, int h, int step) {
    const int x2 = x1 + w, y2 = y1 + h;
    for (int x = x1; x <= x2; x += step) {
        SDL_RenderDrawLine(renderer, x, y1, x, y2);
    }
    for (int y = y1; y <= y2; y += step) {
        SDL_RenderDrawLine(renderer, x1, y, x2, y);
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO != 0)) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    const int WIN_WIDTH = 720, WIN_HEIGHT = 400;
    SDL_Window *win = SDL_CreateWindow(
        "Subway Lines Generator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH,
        WIN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    const int GRID_WIDTH = 368;
    const int GRID_HEIGHT = 208;
    const int GRID_X1 = WIN_WIDTH / 2 - GRID_WIDTH / 2;
    const int GRID_Y1 = WIN_HEIGHT / 2 - GRID_HEIGHT / 2;
    SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
    drawGrid(renderer, GRID_X1, GRID_Y1, GRID_WIDTH, GRID_HEIGHT, 16); // Draw entire grid.

    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
