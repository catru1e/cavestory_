#ifndef SPRITE_H
#define SPRITE_H
/* Sprite class
 * Holds the info of individual sprties
*/
#include "graphics.h"
#include "rectangle.h"
#include "globals.h"

#include <string>
#include <SDL2/SDL.h>

class Graphics;

class Sprite {
public:
    Sprite();
    Sprite(Graphics& graphics, const std::string &filePath, int sourceX,
        int sourceY, int width, int height, float posX, float posY);
    virtual ~Sprite();
    //virtual - bc we gonna hve some stuff in the update probably, but we're gonna be overriding it in animated sprite...
    virtual void update();
    void draw(Graphics& graphics, int x, int y);

    const Rectangle getBoundingBox() const;
    const sides::Side getCollisionSide(Rectangle &other) const;

protected:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;

    Rectangle _boundingBox;

    float _x, _y; //position of the sprite
private:
};

#endif //SPRITE_H
