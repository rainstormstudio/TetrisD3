#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

class Debug {
public:
    static bool enabled;

    static void msg(std::string msg);

    static void msg(std::string msg, unsigned int level);

    static void line();

    static void line(unsigned int level);
};

#endif
