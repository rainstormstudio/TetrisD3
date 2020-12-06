#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "../entityManager.hpp"
#include "../../media.hpp"

class Music : public Component {
    Mix_Music *music;
public:
    double volumeRatio;
    Music(std::string filename);

    ~Music();

    void init() override;

    void pauseMusic();

    void update() override;
    
    void render() override {}
};

#endif
