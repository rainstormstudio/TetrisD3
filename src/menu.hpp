#ifndef MENU_HPP
#define MENU_HPP

#include "texture.hpp"
#include "media.hpp"

class Texture;
class Game;


class Menu {
public:
    enum MenuState {
        TITLE,
        MENU,
        PAUSE_MENU,
        SETTINGS
    };
    MenuState state;
private:
    Texture* titleTexture;
    Mix_Chunk* move_sfx;
    Game* game;
    int option;
    int optionCol;
    int countdown;
    SDL_Rect src;
    SDL_Rect dest;

    double process;
    bool highlight;
    bool clicked;

    MenuState prev_state;
public:

    Menu(Game* game, std::string texturefile, std::string moveSFXfile, SDL_Rect src, SDL_Rect dest);

    ~Menu();

    void reset();

    void choose();

    void triggerMoveSFX();

    void moveOption(int delta);

    void changeSettings(int delta);

    void update();

    void render();
};

#endif
