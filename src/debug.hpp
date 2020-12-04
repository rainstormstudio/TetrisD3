#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

namespace Debug {
    static bool enabled = false;

    void msg(std::string msg);

    void msg(std::string msg, unsigned int level);

    void line();

    void line(unsigned int level);
};

#endif
