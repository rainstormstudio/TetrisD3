#ifndef ROTATELEFT_HPP
#define ROTATELEFT_HPP

#include "../command.hpp"
#include "../EC_Core/entityManager.hpp"
#include "../EC_Core/Components/tetromino.hpp"
#include "../debug.hpp"

class RotateLeft : public Command {
public:
    RotateLeft(Entity* entity) : Command(entity) {}

    void execute() override {
        Tetromino* tetromino = entity->getComponent<Tetromino>();
        tetromino->rotateLeft();
        Debug::msg("rotated left", 1);
        Debug::line(1);
    }
};

#endif
