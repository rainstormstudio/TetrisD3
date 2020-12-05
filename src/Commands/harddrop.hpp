#ifndef HARDDROP_HPP
#define HARDDROP_HPP

#include "../command.hpp"
#include "../EC_Core/entityManager.hpp"
#include "../EC_Core/Components/tetromino.hpp"
#include "../debug.hpp"

class HardDrop : public Command {
public:
    HardDrop(Entity* entity) : Command(entity) {}

    void execute() override {
        Tetromino* tetromino = entity->getComponent<Tetromino>();
        tetromino->harddrop();
        Debug::msg("hard dropped", 1);
        Debug::line(1);
    }
};

#endif
