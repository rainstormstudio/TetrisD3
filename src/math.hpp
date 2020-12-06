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
}

#endif
