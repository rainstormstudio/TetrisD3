#include "soundeffects.hpp"
#include "../../game.hpp"
#include "../../config.hpp"

    void SoundEffects::triggerRotate() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, rotate_sfx, 0);
    }

    void SoundEffects::triggerSoftDrop() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, softdrop_sfx, 0);
    }

    void SoundEffects::triggerHardDrop() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, harddrop_sfx, 0);
    }

    void SoundEffects::triggerSingle() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, single_sfx, 0);
    }

    void SoundEffects::triggerDouble() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, double_sfx, 0);
    }

    void SoundEffects::triggerTriple() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, triple_sfx, 0);
    }

    void SoundEffects::triggerTetris() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, tetris_sfx, 0);
    }

    void SoundEffects::triggerLevelup() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, levelup_sfx, 0);
    }

    void SoundEffects::triggerGameover() {
        Config* cfg = owner->game->getCFG();
        if (cfg->mute_sfx) return;
        Mix_PlayChannel(-1, gameover_sfx, 0);
    }

    void SoundEffects::update() {
        Config* cfg = owner->game->getCFG();
        Mix_Volume(-1, cfg->sfx_volume);
    }