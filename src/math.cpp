#include "math.hpp"
#include <cmath>

void Math::initRandom() {
    srand(time(NULL));
}

int Math::randint(int min, int max) {
    return min + rand() % (max - min + 1);
}

bool Math::isNat(std::string str) {
    int answer = 0;
    try {
        answer = std::stoi(str.c_str());
    } catch (...) {
        return false;
    }
    return true;
}
