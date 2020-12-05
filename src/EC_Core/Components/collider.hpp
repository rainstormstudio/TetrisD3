#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "../entityManager.hpp"
#include "appearance.hpp"
#include <vector>

class Collider : public Component {
    std::vector<std::vector<bool>> collider;
public:
    Collider() {}

    void changeCollider(int x, int y, int w, int h);

    bool willCollide(int rowIndex, int colIndex, int x, int y, int w, int h);

    void init() override {}

    void update() override {}

    void render() override {}

    ~Collider() override {}
};

#endif
