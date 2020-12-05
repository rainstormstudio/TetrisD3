#include "music.hpp"

Music::Music(std::string filename) {
    music = Mix_LoadMUS(filename.c_str());
    if (music == nullptr) {
        std::cerr << "Failed to load music; SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

Music::~Music() {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = nullptr;
}

void Music::pauseMusic() {
    if (Mix_PlayingMusic()) {
        if (Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
        } else {
            Mix_PauseMusic();
        }
    }
}