#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <map>
#include <string>
#include <vector>

#include "sprite.h"
#include "globals.h"

class Graphics;

/*
 * Holds logic for animating sprites
 */
class AnimatedSprite : public Sprite {
public:
  AnimatedSprite();
  AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
                 float posX, float posY, float timeToUpdate);
  //Plays the animation provided if it's nor already playing
  void playAnimation(std::string animation, bool once = false); //IMPORTANT SO MUCH

  //Updates the animated sprite (timer)
  void update(int elapsedTime);

  //Drops the sprite to the screen
  void draw(Graphics &graphics, int x, int y);

  //A required function that sets up all animation for a sprite
  virtual void setupAnimations();

protected:
  double _timeToUpdate;
  bool _currentAnimationOnce;
  std::string _currentAnimation;

  //adds the animation to the map of animations for the sprite
  void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

  //resets all animations associated with this sprite
  void resetAnimations();

  //stops the current animation
  void stopAnimation();

  //changes the visibility  of the animated sprite
  void setVisible(bool visible);

  //logic what happens when an animation ends
  virtual void animationDone(std::string currentAnimation);
private:
    std::map<std::string, std::vector<SDL_Rect>> _animations;
    std::map<std::string, Vector2> _offsets;

    int _frameIndex;
    double _timeElapsed;
    bool _visible; //whether or not the animation is visible
};



#endif
