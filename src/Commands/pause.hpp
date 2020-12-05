#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "../command.hpp"
#include "../EC_Core/entityManager.hpp"
#include "../EC_Core/Components/tetromino.hpp"
#include "../debug.hpp"

class Pause : public Command {
public:
    Pause(Entity* entity) : Command(entity) {}

    void execute() override {
        entity->game->setPause();
        Debug::msg("pause triggerd", 1);
        Debug::line(1);
    }
};

#endif
