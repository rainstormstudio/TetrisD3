#ifndef PANEL_HPP
#define PANEL_HPP

#include "../entityManager.hpp"
#include <chrono>

class Panel : public Component {
    const std::vector<int> points = {
        0,
        40,
        100,
        300,
        1200
    };

    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> current_time;
    int score;
    int level;
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
