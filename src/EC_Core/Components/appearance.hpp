#ifndef APPEARANCE_HPP
#define APPEARANCE_HPP

#include "../entityManager.hpp"

class Texture;
struct CPixel;

class Appearance : public Component {
    Texture* texture;
    CPixel* cpixel;
    SDL_Rect src;
    SDL_Rect dest;
public:
    Appearance(std::string filename);

    Appearance(std::string filename, int x, int y, int w, int h);

    void setSrc(int x, int y, int w, int h);

    void setDest(int x, int y, int w, int h);

    Appearance(Uint8 ch, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba);

    void init() override {}

    void update() override {}

    void render() override;

    ~Appearance();
};

#endif
