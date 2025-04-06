#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();
    ~Graphics();

    void clear();   // Clears the screen
    void present(); // Updates the screen

    SDL_Renderer* getRenderer() const; // Returns the renderer

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
