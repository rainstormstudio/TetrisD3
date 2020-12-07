#include "menu.hpp"
#include "game.hpp"
#include "inputManager.hpp"
#include "texture.hpp"
#include "media.hpp"
#include "config.hpp"
#include "debug.hpp"

Menu::Menu(Game* game, std::string texturefile, std::string moveSFXfile, SDL_Rect src, SDL_Rect dest) 
    : game{game}, src{src}, dest{dest} {
    titleTexture = new Texture(texturefile);
    move_sfx = Mix_LoadWAV(moveSFXfile.c_str());
    if (!move_sfx) std::cerr << "Failed to load sound effect: " << moveSFXfile << Mix_GetError();
    option = 0;
    optionCol = dest.x + 4;
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
    optionCol = dest.x + 4;
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
                case 3: {   // quit game
                    game->state = NO_GAME;
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
                case 3: {   // main menu
                    reset();
                    Debug::msg("call endLevel", 1);
                    game->endLevel();
                    Debug::msg("called endLevel", 1);
                    break;
                }
                case 4: {   // quit game
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
            option = (option + 4 + delta) % 4;
            triggerMoveSFX();
            process = 0.0;
            optionCol = dest.x + 4;
            break;
        }
        case PAUSE_MENU: {
            option = (option + 5 + delta) % 5;
            triggerMoveSFX();
            process = 0.0;
            optionCol = dest.x + 4;
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
            }
            break;
        }
        case MENU: {
            process += deltatime * 70.0;
            if (process > 1.0) {
                optionCol ++;
                if (optionCol > dest.x + 18) {
                    optionCol = dest.x + 18;
                }
                process = 0.0;
            }
            if (event->input[MOVEUP]) {
                moveOption(-1);
            } else if (event->input[MOVEDOWN]) {
                moveOption(+1);
            } else if (event->input[CONFIRM]) {
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
                if (optionCol > dest.x + 18) {
                    optionCol = dest.x + 18;
                }
                process = 0.0;
            }
            if (event->input[MOVEUP]) {
                moveOption(-1);
            } else if (event->input[MOVEDOWN]) {
                moveOption(+1);
            } else if (event->input[CONFIRM]) {
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
            gfx->write("SETTINGS", dest.x + 4, dest.y + 16, 255, 255, 255, 200);
            gfx->write("QUIT GAME", dest.x + 4, dest.y + 18, 255, 255, 255, 200);

            gfx->write(">", dest.x + 2, dest.y + 12 + option * 2, 0, 128, 255, 255);
            for (int i = dest.x + 4; i < optionCol; i ++) {
                gfx->setBackColor(
                    0, 128, 255, 
                    round(255.0 * ((15.0 - i - dest.x - 4) / 15.0)), 
                    i, dest.y + 12 + option * 2);
            }
            if (clicked) {
                if (highlight) {
                    for (int i = 0; i < 10; i ++) {
                        gfx->setBackColor(0, 255, 0, 255, dest.x + i + 4, dest.y + 12 + option * 2);
                    }
                } else {
                    for (int i = 0; i < 10; i ++) {
                        gfx->setBackColor(0, 0, 0, 255, dest.x + i + 4, dest.y + 12 + option * 2);
                    }
                }
            }
            break;
        }
        case PAUSE_MENU: {
            gfx->write("PAUSED", dest.x + 2, dest.y + 2, 255, 255, 255, 255);
            gfx->write("----------", dest.x + 2, dest.y + 3, 255, 255, 255, 255);
            gfx->write("RESUME", dest.x + 4, dest.y + 6, 255, 255, 255, 200);
            gfx->write("RESTART", dest.x + 4, dest.y + 8, 255, 255, 255, 200);
            gfx->write("SETTINGS", dest.x + 4, dest.y + 10, 255, 255, 255, 200);
            gfx->write("MAIN MENU", dest.x + 4, dest.y + 12, 255, 255, 255, 200);
            gfx->write("QUIT GAME", dest.x + 4, dest.y + 14, 255, 255, 255, 200);

            gfx->write(">", dest.x + 2, dest.y + 6 + option * 2, 0, 128, 255, 255);
            for (int i = dest.x + 4; i < optionCol; i ++) {
                gfx->setBackColor(
                    0, 128, 255, 
                    round(255.0 * ((15.0 - i - dest.x - 4) / 15.0)), 
                    i, dest.y + 6 + option * 2);
            }
            if (clicked) {
                if (highlight) {
                    for (int i = 0; i < 10; i ++) {
                        gfx->setBackColor(0, 255, 0, 255, dest.x + i + 4, dest.y + 6 + option * 2);
                    }
                } else {
                    for (int i = 0; i < 10; i ++) {
                        gfx->setBackColor(0, 0, 0, 255, dest.x + i + 4, dest.y + 6 + option * 2);
                    }
                }
            }
            break;
        }
    }
}