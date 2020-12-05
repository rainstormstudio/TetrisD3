#ifndef GAME_HPP
#define GAME_HPP

#include "types.hpp"

using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Config;
class Graphics;
class Command;
class InputManager;
class EntityManager;
class Entity;

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

    Time time_a;
    Time time_b;

public:
    bool tick = false;

    Game();
    ~Game();

    bool loop() const;
    
    void init();

    Entity* createTetro();

    void update();
    void render();

    double getDeltaTime() const;

    void setPause();

    Graphics* getGFX() const;
    InputManager* getEvent() const;
    Config* getCFG() const;

    void executeCommand(std::shared_ptr<Command> command);
};

#endif
