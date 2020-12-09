#ifndef BACKGROUNDEFFECT_HPP
#define BACKGROUNDEFFECT_HPP

#include <math.h>
#include "media.hpp"

class Game;

class BackgroundEffect {
    Game* game;
    SDL_Rect dest;
    double t;

    double r;
    double g;
    double b;

    Uint8 calcR(int n);
    Uint8 calcG(int n);
    Uint8 calcB(int n);

    void adjust(double &value, double target, double deltatime);
public:
    BackgroundEffect(Game* game, SDL_Rect dest);

    void update(double Rratio, double Gratio, double Bratio);

    void render();
};

#endif

