#include "inputManager.hpp"
#include "config.hpp"

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
                    input[i] = true;
                    break;
                } else if (cfg->input[i] == ">" && event.key.keysym.sym == SDLK_PERIOD && SDL_GetModState() & KMOD_SHIFT) {
                    input[i] = true;
                    break;
                } else if (cfg->input[i] == "<" && event.key.keysym.sym == SDLK_COMMA && SDL_GetModState() & KMOD_SHIFT) {
                    input[i] = true;
                    break;
                }
            }
        }
    }
}
