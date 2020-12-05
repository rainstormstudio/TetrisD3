#include "debug.hpp"

bool Debug::enabled = false;

void Debug::msg(std::string msg) {
    if (enabled) {
        std::cout << msg << std::endl;
    }
}

void Debug::msg(std::string msg, unsigned int level) {
    if (enabled) {
        for (unsigned int i = 0; i < level; ++i) {
            std::cout << "    ";
        }
        std::cout << "| " << msg << std::endl;
    }
}

void Debug::line() {
    if (enabled) {
        for (int i = 0; i < 50; ++i) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }
}

void Debug::line(unsigned int level) {
    if (enabled) {
        for (unsigned int i = 0; i < level; ++i) {
            std::cout << "    ";
        }
        for (int i = 0; i < 50; ++i) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }
}
