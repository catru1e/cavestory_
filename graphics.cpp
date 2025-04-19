/*Graphics class
* Holds all the info abt the graphics for the game
*/
#include "graphics.h"

#include <iostream>
#include <SDL_image.h>

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

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
    if (this->spriteSheets.count(filePath) ==  0) {
        this->spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle){
    SDL_RenderCopy(this->renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
    SDL_RenderPresent(this->renderer);
}

void Graphics::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
    SDL_RenderClear(this->renderer);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return this->renderer;
}
