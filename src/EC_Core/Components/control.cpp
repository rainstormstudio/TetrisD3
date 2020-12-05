#include "control.hpp"
#include "../../command.hpp"
#include "../../debug.hpp"
#include "../../commandList.hpp"
#include "../../Exceptions/quitException.hpp"
#include "../../game.hpp"
#include "../../inputManager.hpp"

Control::Control() {}

    void Control::update() {
        owner->game->tick = false;
        InputManager* event = owner->game->getEvent();
        if (event->input[ROTATE_RIGHT]) {
            owner->game->executeCommand(std::make_shared<RotateRight>(owner));
            owner->game->tick = true;
        } else if (event->input[ROTATE_LEFT]) {
            owner->game->executeCommand(std::make_shared<RotateLeft>(owner));
            owner->game->tick = true;
        } else if (event->input[MOVELEFT]) {
            owner->game->executeCommand(std::make_shared<MoveLeft>(owner));
            owner->game->tick = true;
        } else if (event->input[MOVERIGHT]) {
            owner->game->executeCommand(std::make_shared<MoveRight>(owner));
            owner->game->tick = true;
        } else if (event->input[MOVEDOWN]) {
            owner->game->executeCommand(std::make_shared<MoveDown>(owner));
            owner->game->tick = true;
        } else if (event->input[DROP]) {
            owner->game->executeCommand(std::make_shared<HardDrop>(owner));
        }
    }