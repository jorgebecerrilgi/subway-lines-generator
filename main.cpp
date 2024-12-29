#include <SDL2/SDL.h>
#include <iostream>

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

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
