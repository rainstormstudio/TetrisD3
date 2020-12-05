#ifndef MOVEDOWN_HPP
#define MOVEDOWN_HPP

#include "../command.hpp"
#include "../EC_Core/entityManager.hpp"
#include "../EC_Core/Components/tetromino.hpp"
#include "../debug.hpp"

class MoveDown : public Command {
public:
    MoveDown(Entity* entity) : Command(entity) {}

    void execute() override {
        Tetromino* tetromino = entity->getComponent<Tetromino>();
        tetromino->moveDown();
        Debug::msg("moved down", 1);
        Debug::line(1);
    }
};

#endif
