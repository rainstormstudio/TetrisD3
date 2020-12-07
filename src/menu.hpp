#ifndef MENU_HPP
#define MENU_HPP

#include "texture.hpp"
#include "media.hpp"

class Texture;
class Game;


class Menu {
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
public:
    enum MenuState {
        TITLE,
        MENU,
        PAUSE_MENU
    };
    MenuState state;

    Menu(Game* game, std::string texturefile, std::string moveSFXfile, SDL_Rect src, SDL_Rect dest);

    ~Menu();

    void reset();

    void choose();

    void triggerMoveSFX();

    void moveOption(int delta);

    void update();

    void render();
};

#endif
