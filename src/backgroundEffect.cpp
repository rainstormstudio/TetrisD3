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

void BackgroundEffect::adjust(double &value, double target, double deltatime) {
    double speed = 1.0;
    if (value < target) {
        value += deltatime * speed;
        if (value > target) 
            value = target;
    } else if (value > target) {
        value -= deltatime * speed;
        if (value < target)
            value = target;
    }
}

BackgroundEffect::BackgroundEffect(Game* game, SDL_Rect dest) : game{game}, dest{dest} {
    t = 0.0;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

void BackgroundEffect::update(double Rratio, double Gratio, double Bratio) {
    double deltatime = game->getDeltaTime();
    adjust(r, Rratio, deltatime);
    adjust(g, Gratio, deltatime);
    adjust(b, Bratio, deltatime);
    t += deltatime * 120.0;
    if (t > 500.0) {
        t = 0;
    }
}

void BackgroundEffect::render() {
    Media* gfx = game->getGFX();
    for (int i = 0; i < dest.w; i ++) {
        for (int j = 0; j < dest.h; j ++) {
            int x = dest.x + i;
            int y = dest.y + j;
            CPixel* cell = new CPixel{
                0,
                0, 0, 0, 0,
                static_cast<Uint8>(round(r * calcR(i * (dest.h - j)))), 
                static_cast<Uint8>(round(g * calcG((dest.w - i) * j))), 
                static_cast<Uint8>(round(b * calcB(i * j))), 
                255
            };
            gfx->drawPoint(cell, x, y);
            delete cell;
        }
    }
}

