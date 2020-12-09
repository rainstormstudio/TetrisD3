#include "backgroundEffect.hpp"
#include "game.hpp"
#include "debug.hpp"

Uint8 BackgroundEffect::calcR(int n) {
    n += t;
    int x = round(t) + n;
    x += 255;
    x = x % 500;
    return static_cast<Uint8>(abs(255 - x));
}

Uint8 BackgroundEffect::calcG(int n) {
    n += t;
    int x = round(t) + n;
    x = x % 500;
    return static_cast<Uint8>(abs(255 - x));
}

Uint8 BackgroundEffect::calcB(int n) {
    n += t;
    int x = round(t) + n;
    x += 128;
    x = x % 500;
    return static_cast<Uint8>(abs(255 - x));
}

BackgroundEffect::BackgroundEffect(Game* game, SDL_Rect dest) : game{game}, dest{dest} {
    t = 0.0;
}

void BackgroundEffect::update() {
    double deltatime = game->getDeltaTime();
    t += deltatime * 120.0;
    if (t > 500.0) {
        t = 0;
    }
}

void BackgroundEffect::render(double Rratio, double Gratio, double Bratio) {
    Media* gfx = game->getGFX();
    for (int i = 0; i < dest.w; i ++) {
        for (int j = 0; j < dest.h; j ++) {
            int x = dest.x + i;
            int y = dest.y + j;
            CPixel* cell = new CPixel{
                0,
                0, 0, 0, 0,
                static_cast<Uint8>(round(Rratio * calcR(i * (dest.h - j)))), 
                static_cast<Uint8>(round(Gratio * calcG((dest.w - i) * j))), 
                static_cast<Uint8>(round(Bratio * calcB(i * j))), 
                255
            };
            gfx->drawPoint(cell, x, y);
            delete cell;
        }
    }
}

