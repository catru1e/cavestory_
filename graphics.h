#ifndef GRAPHICS_H
#define GRAPHICS_H

/* Graphics class
*  Holds all the info abt the graphics for the game
*/

#include <SDL2/SDL.h>
#include <string>
#include <map>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();
    ~Graphics();
    //loads an image into the spriteSheets map if it doesn't already exist
    SDL_Surface* loadImage(const std::string &filePath);

    //drows a texture to a certain part of the screen
    void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

    void flip(); //renders everything to the screen
    void clear();   // clears the screen

    SDL_Renderer* getRenderer() const; // returns the renderer

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::map<std::string, SDL_Surface*> spriteSheets;
};

#endif
