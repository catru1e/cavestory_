#include "tile.h"
#include "graphics.h"

Tile::Tile(){}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
        _tileset(tileset), _size(size), _titlesetPosition(tilesetPosition),
        _position(Vector2(position.x, position.y))
{}

void Tile::update(int elapsedTime){}
void Tile::draw(Graphics &graphics){
        SDL_Rect destRect = { this->_position.x, this->_position.y,
                this->_size.x, this->_size.y};
        SDL_Rect sourceRect = { this->_titlesetPosition.x, this->_titlesetPosition.y, this->_size.x, this->_size.y };

        graphics.blitSurface(this->_tileset, &sourceRect, &destRect);
}