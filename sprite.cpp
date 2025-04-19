#include "sprite.h"

#include <iostream>
#include <ostream>

#include "graphics.h"

Sprite::Sprite(){}

Sprite::Sprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY,
    int width, int height, float positionX, float positionY) : x(positionX), y(positionY)
{
    this->sourceRect.x = sourceX;
    this->sourceRect.y = sourceY;
    this->sourceRect.w = width;
    this->sourceRect.h = height;

    this->spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (this->spriteSheet == NULL){
        std::cout << "Failed to load sprite texture" << std::endl;
    }
}
Sprite::~Sprite(){}

void Sprite::draw(Graphics& graphics, int x, int y) {
    SDL_Rect destinationRect = {x, y, this->sourceRect.w, this->sourceRect.h};
    graphics.blitSurface(this->spriteSheet, &this->sourceRect, &destinationRect);
}

void Sprite::update() {}