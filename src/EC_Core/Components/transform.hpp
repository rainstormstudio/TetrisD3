#ifndef TRANFORM_HPP
#define TRANFORM_HPP

#include "../entityManager.hpp"
#include "../../math.hpp"

class Transform : public Component {
public:
    Vec2 position;

    Transform() : position{0, 0} {}
    Transform(double x, double y) : position{x, y} {}

    void init() override {}

    void update() override {}

    void render() override {}

    ~Transform() {}
};

#endif
