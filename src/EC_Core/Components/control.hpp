#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "../entityManager.hpp"

class Control : public Component {
public:
    unsigned int speed;

    Control();
    Control(unsigned int speed);

    void init() override {}

    void update() override;

    void render() override {}
};

#endif
