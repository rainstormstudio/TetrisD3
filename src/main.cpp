#include "game.hpp"

#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    Game* game = new Game();
    game->init();

    while (game->loop()) {
        game->update();
        game->render();
    }

    delete game;

    return 0;
}