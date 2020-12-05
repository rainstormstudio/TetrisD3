#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "../entityManager.hpp"
#include "../../media.hpp"

class Music : public Component {
    Mix_Music *music;
public:
    Music(std::string filename);

    ~Music();

    void init() override {
        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(music, -1);
        }
    }

    void pauseMusic();

    void update() override {}
    
    void render() override {}
};

#endif
