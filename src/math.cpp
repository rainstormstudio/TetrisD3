#include "math.hpp"
#include <math.h>

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

std::string Math::format(std::string value, int width, char ch) {
    std::string ans = value;
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

bool Math::isInside(int a, int b, int x, int y, int w, int h) {
    if (a < x || a >= x + w) {
        return false;
    }
    if (b < y || b >= y + h) {
        return false;
    }
    return true;
}

double Math::bellCurve(double x, double sd, double mean) {
    const double PI = 3.14159265358979323846;
    double temp = (x - mean) / sd;
    double y = (1 / sd * sqrt(2 * PI)) * exp(-1.0 / 2.0 * temp * temp);
    return y;
}