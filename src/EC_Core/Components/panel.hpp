#ifndef PANEL_HPP
#define PANEL_HPP

#include "../entityManager.hpp"

struct CPixel;

class Panel : public Component {
    const std::vector<int> points = {
        0,
        40,
        100,
        300,
        1200
    };

    double timepassed;
    int score;
    int level;
    int totallines;
    int lines;

    std::string prefix(int value, int width, char ch);
public:
    Panel();

    void init() override;

    void addlines(int num);

    void update() override;

    void render() override;

};

#endif
