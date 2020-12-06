#include "music.hpp"
#include "../../game.hpp"
#include "../../config.hpp"

Music::Music(std::string filename) {
    music = Mix_LoadMUS(filename.c_str());
    if (music == nullptr) {
        std::cerr << "Failed to load music; SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    volumeRatio = 0.5;
}

Music::~Music() {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = nullptr;
}

void Music::init() {
    Config* cfg = owner->game->getCFG();
    if (cfg->mute_music) return;
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1);
    }
}

void Music::pauseMusic() {
    Config* cfg = owner->game->getCFG();
    if (cfg->mute_music) return;
    if (Mix_PlayingMusic()) {
        if (Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
        } else {
            Mix_PauseMusic();
        }
    }
}

void Music::update() {
    Mix_VolumeMusic(MIX_MAX_VOLUME * volumeRatio);
}