#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "media.hpp"

#include "types.hpp"

enum InputType {
    QUIT,
    MOVEUP,
    MOVEDOWN,
    MOVELEFT,
    MOVERIGHT,
    ROTATE_RIGHT,
    ROTATE_LEFT,
    SOFTDROP,
    HARDDROP,
    PAUSE,
    CONFIRM,
    TOTAL_INPUTTYPES
};

class Config;

class InputManager {
    Config* cfg;
    Media* media;
    SDL_Event event;
public:
    std::vector<bool> input;
    SDL_Rect cursor;    // x: x; y: y; w: button down; h: moved

    InputManager(Config* cfg, Media* media);
    void update();
};

#endif
