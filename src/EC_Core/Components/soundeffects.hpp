#ifndef SOUNDEFFECTS_HPP
#define SOUNDEFFECTS_HPP

#include "../entityManager.hpp"
#include "../../media.hpp"

class SoundEffects : public Component {
    Mix_Chunk* rotate_sfx;
    Mix_Chunk* softdrop_sfx;
    Mix_Chunk* harddrop_sfx;
    Mix_Chunk* single_sfx;
    Mix_Chunk* double_sfx;
    Mix_Chunk* triple_sfx;
    Mix_Chunk* tetris_sfx;
    Mix_Chunk* levelup_sfx;
    Mix_Chunk* gameover_sfx;
public:
    SoundEffects(
        std::string rotate_filename,
        std::string softdrop_filename,
        std::string harddrop_filename,
        std::string single_filename,
        std::string double_filename,
        std::string triple_filename,
        std::string tetris_filename,
        std::string levelup_filename,
        std::string gameover_filename
    ) {
        rotate_sfx = Mix_LoadWAV(rotate_filename.c_str());
        if (!rotate_sfx) std::cerr << "Failed to load sound effect: " << rotate_filename << Mix_GetError() << std::endl;
        softdrop_sfx = Mix_LoadWAV(softdrop_filename.c_str());
        if (!softdrop_sfx) std::cerr << "Failed to load sound effect: " << softdrop_filename << Mix_GetError() << std::endl;
        harddrop_sfx = Mix_LoadWAV(harddrop_filename.c_str());
        if (!harddrop_sfx) std::cerr << "Failed to load sound effect: " << harddrop_filename << Mix_GetError() << std::endl;
        single_sfx = Mix_LoadWAV(single_filename.c_str());
        if (!single_sfx) std::cerr << "Failed to load sound effect: " << single_filename << Mix_GetError() << std::endl;
        double_sfx = Mix_LoadWAV(double_filename.c_str());
        if (!double_sfx) std::cerr << "Failed to load sound effect: " << double_filename << Mix_GetError() << std::endl;
        triple_sfx = Mix_LoadWAV(triple_filename.c_str());
        if (!triple_sfx) std::cerr << "Failed to load sound effect: " << triple_filename << Mix_GetError() << std::endl;
        tetris_sfx = Mix_LoadWAV(tetris_filename.c_str());
        if (!tetris_sfx) std::cerr << "Failed to load sound effect: " << tetris_filename << Mix_GetError() << std::endl;
        levelup_sfx = Mix_LoadWAV(levelup_filename.c_str());
        if (!levelup_sfx) std::cerr << "Failed to load sound effect: " << levelup_filename << Mix_GetError() << std::endl;
        gameover_sfx = Mix_LoadWAV(gameover_filename.c_str());
        if (!gameover_sfx) std::cerr << "Failed to load sound effect: " << gameover_filename << Mix_GetError() << std::endl;
    }

    ~SoundEffects() {
        Mix_FreeChunk(rotate_sfx);
        rotate_sfx = nullptr;
        Mix_FreeChunk(softdrop_sfx);
        softdrop_sfx = nullptr;
        Mix_FreeChunk(harddrop_sfx);
        harddrop_sfx = nullptr;
        Mix_FreeChunk(single_sfx);
        single_sfx = nullptr;
        Mix_FreeChunk(double_sfx);
        double_sfx = nullptr;
        Mix_FreeChunk(triple_sfx);
        triple_sfx = nullptr;
        Mix_FreeChunk(tetris_sfx);
        tetris_sfx = nullptr;
        Mix_FreeChunk(levelup_sfx);
        levelup_sfx = nullptr;
        Mix_FreeChunk(gameover_sfx);
        gameover_sfx = nullptr;
    }

    void triggerRotate();

    void triggerSoftDrop();

    void triggerHardDrop();

    void triggerSingle();

    void triggerDouble();

    void triggerTriple();

    void triggerTetris();

    void triggerLevelup();

    void triggerGameover();

    void init() override {}

    void update() override;

    void render() override {}
};

#endif
