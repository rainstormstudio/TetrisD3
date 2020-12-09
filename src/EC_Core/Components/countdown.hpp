#ifndef COUNTDOWN_HPP
#define COUNTDOWN_HPP

#include "../entityManager.hpp"
#include <vector>
#include <string>

class Countdown : public Component {
    const std::vector<std::vector<std::string>> label = {
        {
            " ###   ### ",
            "#     #   #",
            "# ### #   #",
            "#   # #   #",
            " ###   ### "
        },
        {
            "     #     ",
            "    ##     ",
            "     #     ",
            "     #     ",
            "    ###    "
        },
        {
            "   #####   ",
            "       #   ",
            "   #####   ",
            "   #       ",
            "   #####   "
        },
        {
            "   #####   ",
            "       #   ",
            "   #####   ",
            "       #   ",
            "   #####   "
        }
    };

    double process;
    int number;
public:
    Countdown();

    ~Countdown();

    void init() override {}

    void update() override;

    void render() override;
};

#endif
