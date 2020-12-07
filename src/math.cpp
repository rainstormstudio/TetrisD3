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

std::string Math::format(int value, int width, char ch) {
    std::string ans = std::to_string(value);
    int len = ans.length();
    for (int i = 0; i < width - len; i ++) {
        ans = ch + ans;
    }
    return ans;
}

int Math::max(int a, int b) {
    return std::max(a, b);
}

int Math::min(int a, int b) {
    return std::min(a, b);
}