#ifndef MATH_HPP
#define MATH_HPP

#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

namespace Math {
    void initRandom();

    int randint(int min, int max);

    bool isNat(std::string str);

    std::string format(int value, int width, char ch);

    std::string format(std::string value, int width, char ch);

    int max(int a, int b);

    int min(int a, int b);

    bool isInside(int a, int b, int x, int y, int w, int h);

    double bellCurve(double x, double sd, double mean);
}

#endif
