#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "../entityManager.hpp"
#include "../../media.hpp"

class Music : public Component {
    Mix_Music *music;
    bool active;
public:
    Music(std::string filename);

    ~Music();

    void init() override;

    void getStart();

    void pauseMusic();

    void stopMusic();

    void update() override;
    
    void render() override {}
};

#endif
