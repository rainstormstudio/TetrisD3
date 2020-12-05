#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "../entityManager.hpp"

class Control : public Component {
public:
    Control();

    void init() override {}

    void update() override;

    void render() override {}

    ~Control() override {}
};

#endif
