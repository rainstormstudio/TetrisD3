#include "appearance.hpp"
#include "transform.hpp"
#include "../../game.hpp"
#include "../../media.hpp"
#include "../../texture.hpp"
#include "../../debug.hpp"

Appearance::Appearance(std::string filename) {
    Debug::msg("appearance start", 2);
    texture = new Texture(filename);
    src = {0, 0, 0, 0};
    cpixel = nullptr;
    Debug::msg("appearance end", 2);
}

Appearance::Appearance(std::string filename, int x, int y, int w, int h) {
    texture = new Texture(filename);
    src = {x, y, w, h};
    cpixel = nullptr;
}

void Appearance::setSrc(int x, int y, int w, int h) {
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
}

void Appearance::setDest(int x, int y, int w, int h) {
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
}

Appearance::Appearance(Uint8 ch, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba) {
    texture = nullptr;
    cpixel = new CPixel{};
    cpixel->ch = ch;
    cpixel->r = r;
    cpixel->g = g;
    cpixel->b = b;
    cpixel->a = a;
    cpixel->br = br;
    cpixel->bg = bg;
    cpixel->bb = bb;
    cpixel->ba = ba;
}

void Appearance::render() {
    Media* gfx = owner->game->getGFX();
    Transform* transform = owner->getComponent<Transform>();
    if (cpixel) {
        gfx->drawPoint(cpixel, transform->position.x, transform->position.y);
    } else if (texture) {
        setDest(round(transform->position.x), round(transform->position.y), src.w, src.h);
        gfx->drawTexture(texture, src, dest);
    }
}

Appearance::~Appearance() {
    Debug::msg("delete appearance", 5);
    delete texture;
    texture = nullptr;
    delete cpixel;
    cpixel = nullptr;
    Debug::msg("deleted appearance", 5);
}

