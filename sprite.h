#ifndef SPRITE_H
#define SPRITE_H

/* Sprite class
 * Holds the info of individual sprties
*/

#include "graphics.h"
#include <string>
#include <SDL2/SDL.h>

class Graphics;

class Sprite {
public:
    Sprite();
    Sprite(Graphics& graphics, const std::string &filePath, int sourceX,
        int sourceY, int width, int height, float positionX, float positionY);

    virtual ~Sprite();
    //virtual - bc we gonna hve some stuff in the update probably, but we're gonna be overriding it in animated sprite...
    virtual void update();

    void draw(Graphics& graphics, int x, int y);

private:
    SDL_Rect sourceRect;
    SDL_Texture* spriteSheet;

    float x, y; //position of the sprite
};

#endif //SPRITE_H
