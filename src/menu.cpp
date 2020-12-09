#include "menu.hpp"
#include "game.hpp"
#include "inputManager.hpp"
#include "texture.hpp"
#include "media.hpp"
#include "config.hpp"
#include "saves.hpp"
#include "debug.hpp"
#include "math.hpp"
#include "./EC_Core/entityManager.hpp"
#include "./EC_Core/Components/panel.hpp"

Menu::Menu(Game* game, std::string texturefile, std::string moveSFXfile, SDL_Rect src, SDL_Rect dest) 
    : game{game}, src{src}, dest{dest} {
    titleTexture = new Texture(texturefile);
    move_sfx = Mix_LoadWAV(moveSFXfile.c_str());
    if (!move_sfx) std::cerr << "Failed to load sound effect: " << moveSFXfile << Mix_GetError();
    option = 0;
    optionCol = 0;
    prev_state = TITLE;
    state = TITLE;
    countdown = 0;
    process = 0.0;
    highlight = false;
    clicked = false;
}

Menu::~Menu() {
    Mix_FreeChunk(move_sfx);
    move_sfx = nullptr;
    delete titleTexture;
}

void Menu::reset() {
    option = 0;
    optionCol = 0;
    state = MENU;
    process = 0.0;
    highlight = false;
    clicked = false;
}

void Menu::choose() {
    switch (state) {
        case MENU: {
            switch (option) {
                case 0: {   // start game
                    reset();
                    game->state = IN_GAME;
                    game->createLevel();
                    break;
                }
                case 1: {   // top scores
                    reset();
                    prev_state = MENU;
                    state = SCORES;
                    break;
                }
                case 2: {   // music setting
                    reset();
                    prev_state = MENU;
                    state = MUSIC_SETTING;
                    break;
                }
                case 3: {   // key mapping
                    reset();
                    prev_state = MENU;
                    state = KEY_MAPPING;
                    break;
                }
                case 4: {   // quit game
                    game->state = NO_GAME;
                    break;
                }
            }
            break;
        }
        case PAUSE_MENU: {
            switch (option) {
                case 0: {   // resume
                    reset();
                    game->setPause();
                    break;
                }
                case 1: {   // restart
                    reset();
                    game->endLevel();
                    game->createLevel();
                    break;
                }
                case 2: {   // music settings
                    reset();
                    prev_state = PAUSE_MENU;
                    state = MUSIC_SETTING;
                    break;
                }
                case 3: {   // key mapping
                    reset();
                    prev_state = PAUSE_MENU;
                    state = KEY_MAPPING;
                    break;
                }
                case 4: {   // main menu
                    reset();
                    Debug::msg("call endLevel", 1);
                    game->endLevel();
                    Debug::msg("called endLevel", 1);
                    break;
                }
                case 5: {   // quit game
                    game->state = NO_GAME;
                    break;
                }
            }
            break;
        }
        case MUSIC_SETTING: {
            switch (option) {
                case 4: {   // save settings to config file
                    Config* cfg = game->getCFG();
                    cfg->saveToFile();
                    option = 0;
                    optionCol = 0;
                    process = 0.0;
                    highlight = false;
                    clicked = false;
                    break;
                }
                case 5: {   // back
                    reset();
                    state = prev_state;
                    break;
                }
            }
            break;
        }
        case KEY_MAPPING: {
            switch (option) {
                case 0: {   // back
                    reset();
                    state = prev_state;
                    break;
                }
            }
            break;
        }
        case SCORES: {
            switch (option) {
                case 0: {   // back
                    reset();
                    state = prev_state;
                    break;
                }
            }
            break;
        }
        case END_GAME: {
            switch (option) {
                case 0: {   // restart
                    reset();
                    game->endLevel();
                    game->createLevel();
                    break;
                }
                case 1: {   // current scores
                    reset();
                    prev_state = END_GAME;
                    state = SCORES;
                    break;
                }
                case 2: {   // main menu
                    reset();
                    game->endLevel();
                    break;
                }
                case 3: {   // quit game
                    game->state = NO_GAME;
                    break;
                }
            }
            break;
        }
    }
    
}

void Menu::triggerMoveSFX() {
    Config* cfg = game->getCFG();
    if (cfg->mute_sfx) return;
    Mix_PlayChannel(-1, move_sfx, 0);
}

void Menu::moveOption(int delta) {
    switch (state) {
        case MENU: {
            int lastoption = option;
            if (delta == 0) {
                InputManager* event = game->getEvent();
                if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 12, 10, 1)) {
                    option = 0;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 14, 10, 1)) {
                    option = 1;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 16, 10, 1)) {
                    option = 2;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 18, 10, 1)) {
                    option = 3;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 20, 10, 1)) {
                    option = 4;
                }
            } else {
                option = (option + 5 + delta) % 5;
            }
            if (lastoption == option) break;
            triggerMoveSFX();
            process = 0.0;
            optionCol = 0;
            break;
        }
        case PAUSE_MENU: {
            int lastoption = option;
            if (delta == 0) {
                InputManager* event = game->getEvent();
                if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 6, 10, 1)) {
                    option = 0;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 8, 10, 1)) {
                    option = 1;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 10, 10, 1)) {
                    option = 2;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 12, 10, 1)) {
                    option = 3;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 14, 10, 1)) {
                    option = 4;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x + 2, dest.y + 16, 10, 1)) {
                    option = 5;
                }
            } else {
                option = (option + 6 + delta) % 6;
            }
            if (lastoption == option) break;
            triggerMoveSFX();
            process = 0.0;
            optionCol = 0;
            break;
        }
        case MUSIC_SETTING: {
            int lastoption = option;
            if (delta == 0) {
                InputManager* event = game->getEvent();
                if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 4, 14, 1)) {
                    option = 0;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 6, 14, 1)) {
                    option = 1;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 8, 14, 1)) {
                    option = 2;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 10, 14, 1)) {
                    option = 3;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 12, 14, 1)) {
                    option = 4;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 14, 14, 1)) {
                    option = 5;
                }
            } else {
                option = (option + 6 + delta) % 6;
            }
            if (lastoption == option) break;
            triggerMoveSFX();
            process = 0.0;
            optionCol = 0;
            break;
        }
        case END_GAME: {
            int lastoption = option;
            if (delta == 0) {
                InputManager* event = game->getEvent();
                if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 8, 10, 1)) {
                    option = 0;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 10, 10, 1)) {
                    option = 1;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 12, 10, 1)) {
                    option = 2;
                } else if (Math::isInside(event->cursor.x, event->cursor.y, dest.x, dest.y + 14, 10, 1)) {
                    option = 3;
                }
            } else {
                option = (option + 4 + delta) % 4;
            }
            if (lastoption == option) break;
            triggerMoveSFX();
            process = 0.0;
            optionCol = 0;
            break;
        }
    }
}

void Menu::changeSettings(int delta) {
    Config* cfg = game->getCFG();
    switch (option) {
        case 0: {   // mute music
            cfg->mute_music = !cfg->mute_music;
            break;
        }
        case 1: {   // mute sfx
            cfg->mute_sfx = !cfg->mute_sfx;
            break;
        }
        case 2: {   // music volume
            cfg->music_volume += delta;
            cfg->music_volume = Math::max(cfg->music_volume, 0);
            cfg->music_volume = Math::min(cfg->music_volume, 128);
            break;
        }
        case 3: {   // sfx volume
            cfg->sfx_volume += delta;
            cfg->sfx_volume = Math::max(cfg->sfx_volume, 0);
            cfg->sfx_volume = Math::min(cfg->sfx_volume, 128);
            break;
        }
    }
}

void Menu::update() {
    Config* cfg = game->getCFG();
    Mix_Volume(-1, cfg->sfx_volume);
    double deltatime = game->getDeltaTime();
    InputManager* event = game->getEvent();
    if (clicked) {
        process += deltatime * 30.0;
        if (process > 1.0) {
            highlight = !highlight;
            countdown --;
            if (countdown == 0) {
                choose();
            }
            process = 0.0;
        }
        return;
    }
    switch (state) {
        case TITLE: {
            process += deltatime;
            if (process > 1.0) {
                highlight = !highlight;
                process = 0.0;
            }
            if (event->input[CONFIRM]) {
                triggerMoveSFX();
                state = MENU;
            } else if (event->cursor.w) {
                triggerMoveSFX();
                state = MENU;
            }
            break;
        }
        case MENU: {
            process += deltatime * 70.0;
            if (process > 1.0) {
                optionCol ++;
                if (optionCol > 14) {
                    optionCol = 14;
                }
                process = 0.0;
            }
            if (event->input[MOVEUP]) {
                moveOption(-1);
            } else if (event->input[MOVEDOWN]) {
                moveOption(+1);
            } else if (event->cursor.h) {
                moveOption(0);
            } else if (event->input[CONFIRM]) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->cursor.w) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->input[PAUSE]) {
                reset();
                state = TITLE;
            }
            break;
        }
        case PAUSE_MENU: {
            process += deltatime * 70.0;
            if (process > 1.0) {
                optionCol ++;
                if (optionCol > 14) {
                    optionCol = 14;
                }
                process = 0.0;
            }
            if (event->input[MOVEUP]) {
                moveOption(-1);
            } else if (event->input[MOVEDOWN]) {
                moveOption(+1);
            } else if (event->cursor.h) {
                moveOption(0);
            } else if (event->input[CONFIRM]) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->cursor.w) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->input[PAUSE]) {
                reset();
                game->setPause();
            }
            break;
        }
        case MUSIC_SETTING: {
            process += deltatime * 70.0;
            if (process > 1.0) {
                optionCol ++;
                if (optionCol > 14) {
                    optionCol = 14;
                }
                process = 0.0;
            }
            if (event->input[MOVEUP]) {
                moveOption(-1);
            } else if (event->input[MOVEDOWN]) {
                moveOption(+1);
            } else if (event->cursor.h) {
                moveOption(0);
            } else if (event->input[MOVELEFT]) {
                changeSettings(-1);
            } else if (event->input[MOVERIGHT]) {
                changeSettings(+1);
            } else if (event->input[CONFIRM] && (option == 4 || option == 5)) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->cursor.w && (option == 4 || option == 5)) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->input[PAUSE]) {
                state = prev_state;
            }
            break;
        }
        case KEY_MAPPING: {
            process += deltatime * 70.0;
            if (process > 1.0) {
                optionCol ++;
                if (optionCol > 14) {
                    optionCol = 14;
                }
                process = 0.0;
            }
            if (event->input[CONFIRM] && (option == 0)) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->cursor.w && (option == 0)) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->input[PAUSE]) {
                state = prev_state;
            }
            break;
        }
        case SCORES: {
            process += deltatime * 70.0;
            if (process > 1.0) {
                optionCol ++;
                if (optionCol > 14) {
                    optionCol = 14;
                }
                process = 0.0;
            }
            if (event->input[CONFIRM] && (option == 0)) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->cursor.w && (option == 0)) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->input[PAUSE]) {
                state = prev_state;
            }
            break;
        }
        case END_GAME: {
            process += deltatime * 70.0;
            if (process > 1.0) {
                optionCol ++;
                if (optionCol > 14) {
                    optionCol = 14;
                }
                process = 0.0;
            }
            if (event->input[MOVEUP]) {
                moveOption(-1);
            } else if (event->input[MOVEDOWN]) {
                moveOption(+1);
            } else if (event->cursor.h) {
                moveOption(0);
            } else if (event->input[CONFIRM]) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            } else if (event->cursor.w) {
                clicked = true;
                process = 0.0;
                highlight = true;
                countdown = 8;
            }
            break;
        }
    }
}

void Menu::render() {
    Media* gfx = game->getGFX();
    switch (state) {
        case TITLE: {
            gfx->drawTexture(titleTexture, src, dest);
            if (highlight) {
                gfx->write("PRESS CONFIRM", dest.x + 2, dest.y + 15, 255, 255, 255, 255);
            } else {
                gfx->write("PRESS CONFIRM", dest.x + 2, dest.y + 15, 255, 255, 255, 100);
            }
            break;
        }
        case MENU: {
            gfx->drawTexture(titleTexture, src, dest);
            gfx->write("PLAY GAME", dest.x + 4, dest.y + 12, 255, 255, 255, 200);
            gfx->write("TOP SCORES", dest.x + 4, dest.y + 14, 255, 255, 255, 200);
            gfx->write("MUSIC SETTING", dest.x + 4, dest.y + 16, 255, 255, 255, 200);
            gfx->write("KEY MAPPING", dest.x + 4, dest.y + 18, 255, 255, 255, 200);
            gfx->write("QUIT GAME", dest.x + 4, dest.y + 20, 255, 255, 255, 200);

            gfx->write(">", dest.x + 2, dest.y + 12 + option * 2, 255, 128, 0, 255);
            for (int i = dest.x + 4; i < dest.x + 4 + optionCol; i ++) {
                gfx->addBackColor(
                    255, 128, 0, 
                    round(200.0 * ((optionCol - i + dest.x + 4) / 14.0)), 
                    i, dest.y + 12 + option * 2);
            }
            if (clicked) {
                if (highlight) {
                    for (int i = 0; i < 14; i ++) {
                        gfx->setBackColor(0, 255, 0, 255, dest.x + i + 4, dest.y + 12 + option * 2);
                    }
                } else {
                    for (int i = 0; i < 14; i ++) {
                        gfx->setBackColor(0, 0, 0, 255, dest.x + i + 4, dest.y + 12 + option * 2);
                    }
                }
            }
            break;
        }
        case PAUSE_MENU: {
            gfx->write("PAUSED", dest.x + 2, dest.y + 2, 255, 255, 255, 255);
            gfx->write("=============", dest.x + 2, dest.y + 3, 255, 255, 255, 255);
            gfx->write("RESUME", dest.x + 4, dest.y + 6, 255, 255, 255, 200);
            gfx->write("RESTART", dest.x + 4, dest.y + 8, 255, 255, 255, 200);
            gfx->write("MUSIC SETTING", dest.x + 4, dest.y + 10, 255, 255, 255, 200);
            gfx->write("KEY MAPPING", dest.x + 4, dest.y + 12, 255, 255, 255, 200);
            gfx->write("MAIN MENU", dest.x + 4, dest.y + 14, 255, 255, 255, 200);
            gfx->write("QUIT GAME", dest.x + 4, dest.y + 16, 255, 255, 255, 200);

            gfx->write(">", dest.x + 2, dest.y + 6 + option * 2, 255, 128, 0, 255);
            for (int i = dest.x + 4; i < dest.x + 4 + optionCol; i ++) {
                gfx->addBackColor(
                    255, 128, 0, 
                    round(200.0 * ((optionCol - i + dest.x + 4) / 14.0)), 
                    i, dest.y + 6 + option * 2);
            }
            if (clicked) {
                if (highlight) {
                    for (int i = 0; i < 14; i ++) {
                        gfx->setBackColor(0, 255, 0, 255, dest.x + i + 4, dest.y + 6 + option * 2);
                    }
                } else {
                    for (int i = 0; i < 14; i ++) {
                        gfx->setBackColor(0, 0, 0, 255, dest.x + i + 4, dest.y + 6 + option * 2);
                    }
                }
            }
            break;
        }
        case MUSIC_SETTING: {
            SDL_Rect dest = this->dest;
            dest.x -= 2;
            Config* cfg = game->getCFG();
            gfx->write("MUSIC SETTING", dest.x, dest.y, 255, 255, 255, 255);
            gfx->write("=======================", dest.x, dest.y + 1, 255, 255, 255, 255);
            gfx->write("MUTE MUSIC", dest.x + 2, dest.y + 4, 255, 255, 255, 200);
            gfx->setCh(17, dest.x + 14, dest.y + 4); gfx->setCh(16, dest.x + 18, dest.y + 4);
            gfx->setForeColor(255, 255, 255, 200, dest.x + 14, dest.y + 4);
            gfx->setForeColor(255, 255, 255, 200, dest.x + 18, dest.y + 4);
            if (cfg->mute_music) {
                gfx->write(" ON", dest.x + 15, dest.y + 4, 0, 255, 0, 255);
            } else {
                gfx->write("OFF", dest.x + 15, dest.y + 4, 255, 0, 0, 255);
            }
            gfx->write("MUTE SFX", dest.x + 2, dest.y + 6, 255, 255, 255, 200);
            gfx->setCh(17, dest.x + 14, dest.y + 6); gfx->setCh(16, dest.x + 18, dest.y + 6);
            gfx->setForeColor(255, 255, 255, 200, dest.x + 14, dest.y + 6);
            gfx->setForeColor(255, 255, 255, 200, dest.x + 18, dest.y + 6);
            if (cfg->mute_sfx) {
                gfx->write(" ON", dest.x + 15, dest.y + 6, 0, 255, 0, 255);
            } else {
                gfx->write("OFF", dest.x + 15, dest.y + 6, 255, 0, 0, 255);
            }
            gfx->write("MUSIC VOLUME", dest.x + 2, dest.y + 8, 255, 255, 255, 200);
            gfx->setCh(17, dest.x + 14, dest.y + 8); gfx->setCh(16, dest.x + 18, dest.y + 8);
            gfx->setForeColor(255, 255, 255, 200, dest.x + 14, dest.y + 8);
            gfx->setForeColor(255, 255, 255, 200, dest.x + 18, dest.y + 8);
            gfx->write(Math::format(cfg->music_volume, 3, ' '), dest.x + 15, dest.y + 8, 255, 255, 0, 255);
            gfx->write("SFX VOLUME", dest.x + 2, dest.y + 10, 255, 255, 255, 200);
            gfx->setCh(17, dest.x + 14, dest.y + 10); gfx->setCh(16, dest.x + 18, dest.y + 10);
            gfx->setForeColor(255, 255, 255, 200, dest.x + 14, dest.y + 10);
            gfx->setForeColor(255, 255, 255, 200, dest.x + 18, dest.y + 10);
            gfx->write(Math::format(cfg->sfx_volume, 3, ' '), dest.x + 15, dest.y + 10, 255, 255, 0, 255);
            gfx->write("SAVE TO CONFIG", dest.x + 2, dest.y + 12, 255, 255, 255, 200);
            gfx->write("BACK", dest.x + 2, dest.y + 14, 255, 255, 255, 200);

            gfx->write(">", dest.x, dest.y + 4 + option * 2, 255, 128, 0, 255);
            for (int i = dest.x + 2; i < dest.x + 2 + optionCol; i ++) {
                gfx->addBackColor(
                    255, 128, 0, 
                    round(200.0 * ((optionCol - i + dest.x + 2) / 14.0)),
                    i, dest.y + 4 + option * 2);
            }
            if (clicked) {
                if (highlight) {
                    for (int i = 0; i < 16; i ++) {
                        gfx->setBackColor(0, 255, 0, 255, dest.x + i + 2, dest.y + 4 + option * 2);
                    }
                } else {
                    for (int i = 0; i < 16; i ++) {
                        gfx->setBackColor(0, 0, 0, 255, dest.x + i + 2, dest.y + 4 + option * 2);
                    }
                }
            }
            break;
        }
        case KEY_MAPPING: {
            Config* cfg = game->getCFG();
            SDL_Rect dest = this->dest;
            dest.x -= 4;
            gfx->write("KEY MAPPING", dest.x, dest.y, 255, 255, 255, 255);
            gfx->write("=====================", dest.x, dest.y + 1, 255, 255, 255, 255);

            gfx->write("CURRENT CONFIG FILE:", dest.x + 2, dest.y + 2, 255, 255, 255, 200);
            gfx->write("./config/config.txt", dest.x + 2, dest.y + 3, 255, 255, 255, 200);
            gfx->write("UP           " + Math::format(cfg->input[MOVEUP], 8, ' '), dest.x + 2, dest.y + 5, 255, 255, 255, 200);
            gfx->write("DOWN         " + Math::format(cfg->input[MOVEDOWN], 8, ' '), dest.x + 2, dest.y + 6, 255, 255, 255, 200);
            gfx->write("LEFT         " + Math::format(cfg->input[MOVELEFT], 8, ' '), dest.x + 2, dest.y + 7, 255, 255, 255, 200);
            gfx->write("RIGHT        " + Math::format(cfg->input[MOVERIGHT], 8, ' '), dest.x + 2, dest.y + 8, 255, 255, 255, 200);
            gfx->write("ROTATE RIGHT " + Math::format(cfg->input[ROTATE_RIGHT], 8, ' '), dest.x + 2, dest.y + 9, 255, 255, 255, 200);
            gfx->write("ROTATE LEFT  " + Math::format(cfg->input[ROTATE_LEFT], 8, ' '), dest.x + 2, dest.y + 10, 255, 255, 255, 200);
            gfx->write("HARD DROP    " + Math::format(cfg->input[DROP], 8, ' '), dest.x + 2, dest.y + 11, 255, 255, 255, 200);
            gfx->write("PAUSE        " + Math::format(cfg->input[PAUSE], 8, ' '), dest.x + 2, dest.y + 12, 255, 255, 255, 200);
            gfx->write("CONFIRM      " + Math::format(cfg->input[CONFIRM], 8, ' '), dest.x + 2, dest.y + 13, 255, 255, 255, 200);
            gfx->write("PLEASE USE CONFIG", dest.x, dest.y + 15, 255, 255, 255, 200);
            gfx->write("FILE FOR ADJUSTMENT", dest.x, dest.y + 16, 255, 255, 255, 200);

            gfx->write("BACK", dest.x + 2, dest.y + 18, 255, 255, 255, 200);

            gfx->write(">", dest.x, dest.y + 18, 255, 128, 0, 255);
            for (int i = dest.x + 2; i < dest.x + 2 + optionCol; i ++) {
                gfx->addBackColor(
                    255, 128, 0, 
                    round(200.0 * ((optionCol - i + dest.x + 2) / 14.0)),
                    i, dest.y + 18);
            }
            if (clicked) {
                if (highlight) {
                    for (int i = 0; i < 16; i ++) {
                        gfx->setBackColor(0, 255, 0, 255, dest.x + i + 2, dest.y + 18);
                    }
                } else {
                    for (int i = 0; i < 16; i ++) {
                        gfx->setBackColor(0, 0, 0, 255, dest.x + i + 2, dest.y + 18);
                    }
                }
            }
            break;
        }
        case SCORES: {
            Saves* saves = game->getSaves();
            gfx->write("TOP SCORES", dest.x, dest.y, 255, 255, 255, 255);
            gfx->write("================", dest.x, dest.y + 1, 255, 255, 255, 255);
            std::vector<int> scores = saves->getScores(6);
            for (int i = 0; i < 6; i ++) {
                gfx->write(std::to_string(i + 1) + ". " + Math::format(scores[i], 10, ' '), dest.x + 2, dest.y + 3 + i * 2, 255, 255, 255, 200);
            }
            gfx->write("BACK", dest.x + 2, dest.y + 17, 255, 255, 255, 200);
            gfx->write(">", dest.x, dest.y + 17, 255, 128, 0, 255);
            for (int i = dest.x + 2; i < dest.x + 2 + optionCol; i ++) {
                gfx->addBackColor(
                    255, 128, 0, 
                    round(200.0 * ((optionCol - i + dest.x + 2) / 14.0)),
                    i, dest.y + 17);
            }
            if (clicked) {
                if (highlight) {
                    for (int i = 0; i < 16; i ++) {
                        gfx->setBackColor(0, 255, 0, 255, dest.x + i + 2, dest.y + 17);
                    }
                } else {
                    for (int i = 0; i < 16; i ++) {
                        gfx->setBackColor(0, 0, 0, 255, dest.x + i + 2, dest.y + 17);
                    }
                }
            }
            break;
        }
        case END_GAME: {
            gfx->write("GAME OVER", dest.x, dest.y, 255, 255, 255, 255);
            gfx->write("====================", dest.x, dest.y + 1, 255, 255, 255, 255);
            Entity* interface = game->getEntityManager()->getEntityByName("Interface");
            Panel* panel = interface->getComponent<Panel>();
            int score = panel->getScore();
            std::vector<int> times = panel->getTime();
            std::string time = Math::format(times[0], 2, '0') + ":" + Math::format(times[1], 2, '0') + ":" + Math::format(times[2], 2, '0');
            gfx->write("SCORE:      " + Math::format(score, 8, ' '), dest.x, dest.y + 3, 255, 255, 255, 200);
            gfx->write("TIME:       " + Math::format(time, 8, ' '), dest.x, dest.y + 5, 255, 255, 255, 200);

            gfx->write("NEXT GAME", dest.x + 2, dest.y + 8, 255, 255, 255, 200);
            gfx->write("CURRENT SCORES", dest.x + 2, dest.y + 10, 255, 255, 255, 200);
            gfx->write("MAIN MENU", dest.x + 2, dest.y + 12, 255, 255, 255, 200);
            gfx->write("QUIT", dest.x + 2, dest.y + 14, 255, 255, 255, 200);
            gfx->write(">", dest.x, dest.y + 8 + option * 2, 255, 128, 0, 255);
            for (int i = dest.x + 2; i < dest.x + 2 + optionCol; i ++) {
                gfx->addBackColor(
                    255, 128, 0, 
                    round(200.0 * ((optionCol - i + dest.x + 2) / 14.0)),
                    i, dest.y + 8 + option * 2);
            }
            if (clicked) {
                if (highlight) {
                    for (int i = 0; i < 16; i ++) {
                        gfx->setBackColor(0, 255, 0, 255, dest.x + i + 2, dest.y + 8 + option * 2);
                    }
                } else {
                    for (int i = 0; i < 16; i ++) {
                        gfx->setBackColor(0, 0, 0, 255, dest.x + i + 2, dest.y + 8 + option * 2);
                    }
                }
            }

            break;
        }
    }
}