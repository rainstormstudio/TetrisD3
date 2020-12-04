#include "control.hpp"
#include "../../command.hpp"
#include "../../commandList.hpp"
#include "../../Exceptions/quitException.hpp"
#include "../../game.hpp"
#include "../../inputManager.hpp"

    Control::Control() : speed{1} {}
    Control::Control(unsigned int speed) : speed{speed} {}

    void Control::update() {
        owner->game->tick = false;
        InputManager* event = owner->game->getEvent();
        if (event->input[MOVEUP]) {
            
            owner->game->tick = true;
        } else if (event->input[MOVEDOWN]) {
            
            owner->game->tick = true;
        } else if (event->input[MOVELEFT]) {
            
            owner->game->tick = true;
        } else if (event->input[MOVERIGHT]) {
            
            owner->game->tick = true;
        } 
    }