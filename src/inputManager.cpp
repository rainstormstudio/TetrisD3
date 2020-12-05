#include "inputManager.hpp"
#include "config.hpp"
#include "debug.hpp"

InputManager::InputManager(Config* cfg) : cfg{cfg} {
    input = std::vector<bool>(TOTAL_INPUTTYPES);
}

void InputManager::update() {
    for (int i = 0; i < TOTAL_INPUTTYPES; ++i) {
        input[i] = false;
    }
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            input[QUIT] = true;
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
