#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "animatedsprite.h"
#include "globals.h"

class Graphics;

class Player : public AnimatedSprite {
public:
    Player();
    Player(Graphics &graphics, Vector2 spawnPoint);

    void draw(Graphics &graphics);
    void update(float elapsedTime);

    void moveLeft(); // moving left by -dx
    void moveRight(); // moving right by dx
    void stopMoving();

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();

    //handles collisions with all tiles the player is colliding with
    void handleTileCollisions(std::vector<Rectangle> &others);

    const float getX() const;
    const float getY() const;
private:
    float _dx, _dy;

    Direction _facing;

    bool _grounded;
};

#endif //PLAYER_H
