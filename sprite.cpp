#include "sprite.h"
#include "graphics.h"
#include "globals.h"

#include <iostream>

Sprite::Sprite(){}

Sprite::Sprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY,
    int width, int height, float positionX, float positionY) : x(positionX), y(positionY)
{
    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = width;
    this->_sourceRect.h = height;

    this->spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (this->spriteSheet == NULL){
        std::cout << "Failed to load sprite texture\n";
    }
}
Sprite::~Sprite(){}

void Sprite::draw(Graphics& graphics, int x, int y) {
    SDL_Rect destinationRect = {x, y, this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h * globals::SPRITE_SCALE};
    graphics.blitSurface(this->spriteSheet, &this->_sourceRect, &destinationRect);
}

void Sprite::update()
{

}