#ifndef ROTATERIGHT_HPP
#define ROTATERIGHT_HPP

#include "../command.hpp"
#include "../EC_Core/entityManager.hpp"
#include "../EC_Core/Components/tetromino.hpp"
#include "../debug.hpp"

class RotateRight : public Command {
public:
    RotateRight(Entity* entity) : Command(entity) {}

    void execute() override {
        Tetromino* tetromino = entity->getComponent<Tetromino>();
        tetromino->rotateRight();
        Debug::msg("rotated right", 1);
        Debug::line(1);
    }
};

#endif
