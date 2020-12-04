#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#ifdef __linux__
#include "SDL2/SDL.h"
#elif _WIN32
#include "SDL.h"
#endif

#include "types.hpp"

enum InputType {
    QUIT,
    MOVEUP,
    MOVEDOWN,
    MOVELEFT,
    MOVERIGHT,
    ROTATE_RIGHT,
    ROTATE_LEFT,
    DROP,
    PAUSE,
    CONFIRM,
    TOTAL_INPUTTYPES
};

class Config;

class InputManager {
    Config* cfg;
    SDL_Event event;
public:
    std::vector<bool> input;

    InputManager(Config* cfg);
    void update();
};

#endif
