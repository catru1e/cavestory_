/* Input class
 * Keeps track of keyboard state
*/
#include "input.h"

#include <SDL2/SDL.h>

//reseting the keys that are no longer relevant (get called in at the beginning of each new frame)
void Input::beginNewFrame(){
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
}
//this is called when a key has been pressed
void Input::keyDownEvent(const SDL_Event& event){
    this-> _pressedKeys[event.key.keysym.scancode] = true;
    this-> _heldKeys[event.key.keysym.scancode] = true;
}
//this is called when a key is released
void Input::keyUpEvent(const SDL_Event& event){
    this->_releasedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false;
}
//checking if the key was pressed
bool Input::wasKeyPressed(SDL_Scancode key){
    return this->_pressedKeys[key];
}
//checking if the key was released
bool Input::wasKeyReleased(SDL_Scancode key){
    return this->_releasedKeys[key];
}
//checking if the key is being held
bool Input::isKeyHeld(SDL_Scancode key){
    return this->_heldKeys[key];
}


