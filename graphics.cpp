// #include <SDL2/SDL.h>
// #include "graphics.h"
//
// /* Graphics class
//  * Holds all the info abt the graphics for the game
//  */
// Graphics::Graphics() {
//     SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
//     SDL_SetWindowTitle(this->_window, "Cave Story");
// }
// Graphics::~Graphics(){
//     SDL_DestroyWindow(this->_window);
// }
#include "graphics.h"

#include <iostream>
#include <SDL2/SDL.h>

Graphics::Graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("Cave Story", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
    SDL_RenderClear(renderer);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return renderer;
}
