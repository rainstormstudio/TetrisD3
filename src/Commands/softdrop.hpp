#ifndef SOFTDROP_HPP
#define SOFTDROP_HPP

#include "../command.hpp"
#include "../EC_Core/entityManager.hpp"
#include "../EC_Core/Components/tetromino.hpp"
#include "../debug.hpp"

class SoftDrop : public Command {
public:
    SoftDrop(Entity* entity) : Command(entity) {}

    void execute() override {
        Tetromino* tetromino = entity->getComponent<Tetromino>();
        tetromino->moveDown();
        Debug::msg("moved down", 1);
        Debug::line(1);
    }
};

#endif
