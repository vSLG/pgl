#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char **argv) {
    std::cout << "Hello world!\n";

    const char *title  = "Hello world";
    int         width  = 600;
    int         height = 400;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
        title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    return 0;
}