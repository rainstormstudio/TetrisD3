#ifndef BACKGROUNDEFFECT_HPP
#define BACKGROUNDEFFECT_HPP

#include <math.h>
#include "media.hpp"

class Game;

class BackgroundEffect {
    Game* game;
    SDL_Rect dest;
    double t;

    Uint8 calcR(int n);
    Uint8 calcG(int n);
    Uint8 calcB(int n);
public:
    BackgroundEffect(Game* game, SDL_Rect dest);

    void update();

    void render(double Rratio, double Gratio, double Bratio);
};

#endif

