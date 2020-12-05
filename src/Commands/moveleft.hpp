#ifndef MOVELEFT_HPP
#define MOVELEFT_HPP

#include "../command.hpp"
#include "../EC_Core/entityManager.hpp"
#include "../EC_Core/Components/tetromino.hpp"
#include "../debug.hpp"

class MoveLeft : public Command {
    int delta;
public:
    MoveLeft(Entity* entity) : Command(entity), delta{1} {}

    void execute() override {
        Tetromino* tetromino = entity->getComponent<Tetromino>();
        tetromino->moveLeft();
        Debug::msg("moved left", 1);
        Debug::line(1);
    }
};

#endif
