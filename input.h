#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL2/SDl.h>

class Input {
public:
    void beginNewFrame();
    void keyUpEvent(const SDL_Event &event); // when key is pressed
    void keyDownEvent(const SDL_Event &event); // when key was released

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);
private:
    std::map<SDL_Scancode, bool> _heldKeys;
    std::map<SDL_Scancode, bool> _pressedKeys;
    std::map<SDL_Scancode, bool> _releasedKeys;
};



#endif //INPUT_H
