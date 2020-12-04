#ifndef PANEL_HPP
#define PANEL_HPP

#include "../entityManager.hpp"

class Panel : public Component {
protected:
    unsigned int width;
    unsigned int height;
    Vec2 posOnScreen;
public:
    Panel(unsigned int width, unsigned int height, Vec2 posOnScreen);

    void drawBorderBold(std::string title, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void drawBorder(std::string title, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void fillBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void fillBackColorGradient(Uint8 r, Uint8 g, Uint8 b, Uint8 a, unsigned int threshold, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void fillForeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void fillForeColorGradient(Uint8 r, Uint8 g, Uint8 b, Uint8 a, unsigned int threshold, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void init() override {}

    void update() override {}

    void render() override {}
};

#endif
