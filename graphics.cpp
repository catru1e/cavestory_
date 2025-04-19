/*Graphics class
* Holds all the info abt the graphics for the game
*/
#include "graphics.h"
#include "globals.h"

#include <iostream>
#include <SDL_image.h>

Graphics::Graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->window, &this->renderer);
    //  window = SDL_CreateWindow("Cave Story", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_SetWindowTitle(this->window, "CaveStory");
    //  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics() {
    SDL_DestroyWindow(this->window);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
    if (this->spriteSheets.count(filePath) == 0) {
        SDL_Surface* loadedImage = IMG_Load(filePath.c_str());
        if (!loadedImage) {
            std::cerr << "IMG_Load failed for '" << filePath << "': " << IMG_GetError() << std::endl;
        } else {
            this->spriteSheets[filePath] = loadedImage;
        }
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
    SDL_RenderClear(this->renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return this->renderer;
}
