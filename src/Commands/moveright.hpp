#ifndef MOVERIGHT_HPP
#define MOVERIGHT_HPP

#include "../command.hpp"
#include "../EC_Core/entityManager.hpp"
#include "../EC_Core/Components/tetromino.hpp"
#include "../debug.hpp"

class MoveRight : public Command {
    int delta;
public:
    MoveRight(Entity* entity) : Command(entity), delta{1} {}

    void execute() override {
        Tetromino* tetromino = entity->getComponent<Tetromino>();
        tetromino->moveRight();
        Debug::msg("moved right", 1);
        Debug::line(1);
    }
};

#endif
