#include <SDL2/SDL.h>
#include <iostream>

const int WIN_WIDTH = 720;
const int WIN_HEIGHT = 400;
const int GRID_WIDTH = 368;
const int GRID_HEIGHT = 208;
const int GRID_STEP = 16;
const SDL_Color GRID_COLOR = { 210, 210, 210, 255 };

void drawGrid(SDL_Renderer *renderer, int x1, int y1, int w, int h, int step, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
        "Subway Lines Generator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH,
        WIN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (win == NULL) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Draw the background white.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw grid on the center of the screen.
    const int GRID_X1 = (WIN_WIDTH - GRID_WIDTH) /2;
    const int GRID_Y1 = (WIN_HEIGHT - GRID_HEIGHT) / 2;
    drawGrid(renderer, GRID_X1, GRID_Y1, GRID_WIDTH, GRID_HEIGHT, GRID_STEP, GRID_COLOR);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        SDL_WaitEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
