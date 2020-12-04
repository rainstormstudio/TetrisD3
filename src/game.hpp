#ifndef GAME_HPP
#define GAME_HPP

#include "types.hpp"

class Config;
class Graphics;
class Command;
class InputManager;
class EntityManager;

enum GameState {
    NO_GAME,
    MENU,
    IN_GAME,
    PAUSE_MENU
};

class Game {
    GameState state;
    Config* cfg;
    Graphics* gfx;
    InputManager* event;
    EntityManager* manager;

public:
    bool tick = false;

    Game();
    ~Game();

    bool loop() const;
    
    void init();

    void update();
    void render();

    Graphics* getGFX() const;
    InputManager* getEvent() const;
    Config* getCFG() const;

    void executeCommand(std::shared_ptr<Command> command);
};

#endif
