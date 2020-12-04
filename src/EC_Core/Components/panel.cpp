#include "panel.hpp"
#include "../../graphics.hpp"

    Panel::Panel(unsigned int width, unsigned int height, Vec2 posOnScreen)
        : width{width}, height{height}, posOnScreen{posOnScreen} {}

    void Panel::drawBorderBold(std::string title, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        unsigned int top = posOnScreen.y + y;
        unsigned int left = posOnScreen.x + x;
        Graphics* gfx = owner->game->getGFX();
        for (unsigned int i = 1; i < h - 1; ++i) {
            gfx->setCh(186, left, top + i);
            gfx->setCh(186, left + w - 1, top + i);
        }
        for (unsigned int i = 1; i < w - 1; ++i) {
            gfx->setCh(205, left + i, top);
            gfx->setCh(205, left + i, top + height - 1);
        }
        gfx->setCh(201, left, top);
        gfx->setCh(187, left + w - 1, top);
        gfx->setCh(200, left, top + h - 1);
        gfx->setCh(188, left + w - 1, top + h - 1);
        if (title != "" && title.length() < w - 2) {
            gfx->write("[" + title + "]", left + 1, top);
        }
    }

    void Panel::drawBorder(std::string title, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        unsigned int top = posOnScreen.y + y;
        unsigned int left = posOnScreen.x + x;
        Graphics* gfx = owner->game->getGFX();
        for (unsigned int i = 1; i < h - 1; ++i) {
            gfx->setCh(179, left, top + i);
            gfx->setCh(179, left + w - 1, top + i);
        }
        for (unsigned int i = 1; i < w - 1; ++i) {
            gfx->setCh(196, left + i, top);
            gfx->setCh(196, left + i, top + h - 1);
        }
        gfx->setCh(218, left, top);
        gfx->setCh(191, left + w - 1, top);
        gfx->setCh(192, left, top + h - 1);
        gfx->setCh(217, left + w - 1, top + h - 1);
        if (title != "" && title.length() < w - 2) {
            gfx->write("[" + title + "]", left + 1, top);
        }
    }

    void Panel::fillBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        unsigned int top = posOnScreen.y + y;
        unsigned int left = posOnScreen.x + x;
        Graphics* gfx = owner->game->getGFX();
        for (unsigned int i = 0; i < h; ++i) {
            for (unsigned int j = 0; j < w; ++j) {
                gfx->setBackColor(r, g, b, a, j + left, i + top);
            }
        }
    }

    void Panel::fillBackColorGradient(Uint8 r, Uint8 g, Uint8 b, Uint8 a, unsigned int threshold, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        unsigned int top = posOnScreen.y + y;
        unsigned int left = posOnScreen.x + x;
        if (threshold + r > 255) threshold = 255 - r;
        Graphics* gfx = owner->game->getGFX();
        for (unsigned int i = 0; i < h; ++i) {
            for (unsigned int j = 0; j < w; ++j) {
                gfx->setBackColor(r + threshold * (i + j) / (w + h), 
                                    g + threshold * (i + j) / (w + h), 
                                    b + threshold * (i + j) / (w + h), 
                                    a, j + left, i + top);
            }
        }
    }

    void Panel::fillForeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        unsigned int top = posOnScreen.y + y;
        unsigned int left = posOnScreen.x + x;
        Graphics* gfx = owner->game->getGFX();
        for (unsigned int i = 0; i < h; ++i) {
            for (unsigned int j = 0; j < w; ++j) {
                gfx->setForeColor(r, g, b, a, j + left, i + top);
            }
        }
    }

    void Panel::fillForeColorGradient(Uint8 r, Uint8 g, Uint8 b, Uint8 a, unsigned int threshold, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
        unsigned int top = posOnScreen.y + y;
        unsigned int left = posOnScreen.x + x;
        if (threshold + r > 255) threshold = 255 - r;
        Graphics* gfx = owner->game->getGFX();
        for (unsigned int i = 0; i < h; ++i) {
            for (unsigned int j = 0; j < w; ++j) {
                gfx->setForeColor(r + threshold * (i + j) / (w + h), 
                                    g + threshold * (i + j) / (w + h), 
                                    b + threshold * (i + j) / (w + h), 
                                    a, j + left, i + top);
            }
        }
    }