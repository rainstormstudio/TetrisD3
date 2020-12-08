#include "inputManager.hpp"
#include "config.hpp"
#include "debug.hpp"
#include "media.hpp"

InputManager::InputManager(Config* cfg, Media* media) : cfg{cfg}, media{media} {
    input = std::vector<bool>(TOTAL_INPUTTYPES, false);
    cursor = {0, 0, 0, 0};
}

void InputManager::update() {
    for (int i = 0; i < TOTAL_INPUTTYPES; ++i) {
        input[i] = false;
    }
    cursor = {-1, -1, 0, 0};
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            input[QUIT] = true;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            cursor.w = 1;
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            cursor.w = 0;
        } else if (event.type == SDL_MOUSEMOTION) {
            cursor.h = 1;
            int x, y;
            SDL_GetMouseState(&x, &y);
            cursor.x = media->getPosCol(x);
            cursor.y = media->getPosRow(y);
        } else if (event.type == SDL_KEYDOWN) {
            for (int i = 0; i < TOTAL_INPUTTYPES; ++i) {
                if (event.key.keysym.sym == SDL_GetKeyFromName(cfg->input[i].c_str())) {
                    Debug::msg("input[" + std::to_string(i) + "]: " + cfg->input[i], 1);
                    input[i] = true;
                }
            }
        }
    }        
}
