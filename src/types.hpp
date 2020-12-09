#ifndef TYPES_HPP
#define TYPES_HPP

#ifdef __linux__
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#elif _WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#endif

#include <vector>
#include <stack>
#include <map>
#include <string>
#include <memory>
#include <chrono>

struct Vec2 {
    const double epsilon = 0.000001;
    double x = 0.0;
    double y = 0.0;

    Vec2(double x, double y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &v) {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 operator-(const Vec2 &v) {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 operator+=(const Vec2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2 operator-=(const Vec2 &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    bool operator==(const Vec2 &v) {
        return abs(x - v.x) < epsilon && abs(y - v.y) < epsilon;
    }

    bool operator!=(const Vec2 &v) {
        return !(x == v.x && y == v.y);
    }
};

namespace Layer {
    enum Type {
        MAP,
        OBJECTS,
        UI,
        TOTAL
    };
};

#endif
