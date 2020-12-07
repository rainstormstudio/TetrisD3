#include "music.hpp"
#include "../../game.hpp"
#include "../../config.hpp"

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

void Music::init() {
    Config* cfg = owner->game->getCFG();
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music, -1);
    }
    if (cfg->mute_music) {
        Mix_PauseMusic();
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

void Music::stopMusic() {
    if (Mix_PlayingMusic() && Mix_PausedMusic() != 1) {
        Mix_PauseMusic();
    }
}

void Music::update() {
    Config* cfg = owner->game->getCFG();
    Mix_VolumeMusic(cfg->music_volume);
}