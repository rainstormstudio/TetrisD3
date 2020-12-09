#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "../entityManager.hpp"
#include "../../game.hpp"
#include "../../command.hpp"
#include "../../commandList.hpp"
#include "../../debug.hpp"

class Gravity : public Component {
    double speed;
    double process;
public:
    Gravity(double speed) : speed{speed} {
        process = 0.0;
    }

    void init() override {}

    void setSpeed(double value) {
        speed = value;
    }

    double getSpeed() const {
        return speed;
    }

    void update() override {
        double deltatime = owner->game->getDeltaTime();
        Debug::msg("deltatime = " + std::to_string(deltatime), 1);
        process += speed * deltatime;
        Debug::msg("process = " + std::to_string(process), 1);
        if (process >= 1.0) {
            owner->game->executeCommand(std::make_shared<SoftDrop>(owner));
            process = 0.0;
        }
    }

    void render() override {}

    ~Gravity() override {}
};

#endif
