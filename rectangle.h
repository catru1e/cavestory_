#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

class Rectangle {
public:
    Rectangle() {}
    Rectangle(int x, int y, int width, int height) :
        _x(x), _y(y), _width(width), _height(height) {}

    const int getCenterX() const { return this->_x + this->_width / 2; }
    const int getCenterY() const { return this->_y + this->_height / 2; }

    const int getLeft() const { return this->_x; }
    const int getRight() const { return this->_x + this->_width; }
    const int getTop() const { return this->_y; }
    const int getBottom() const { return this->_y + this->_height; }

    const int getWidth() const { return this->_width; }
    const int getHeight() const { return this->_height; }

    const int getSide (const sides::Side side) const {
        switch (side) {
            case sides::LEFT: return this->getLeft();
            case sides::RIGHT: return this->getRight();
            case sides::TOP: return this->getTop();
            case sides::BOTTOM: return this->getBottom();
            default: return -1; // or std::invalid_argument
        }
    }

    //gets in another rectangle and checks if two are colliding
    const bool collidesWith(const Rectangle &other) const {
        return
                this->getRight() >= other.getLeft() &&
                this->getLeft() <= other.getRight() &&
                this->getTop() <= other.getBottom() &&
                this->getBottom() >= other.getTop();
        //if all of this is true, return true.
    }

    const bool isValidRectangle() const {
        return (this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0);
    }
private:
    int _x;
    int _y;
    int _width;
    int _height;

};

#endif //RECTANGLE_H
