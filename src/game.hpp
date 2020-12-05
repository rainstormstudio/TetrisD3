#ifndef GAME_HPP
#define GAME_HPP

#include "types.hpp"

using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Config;
class Media;
class Command;
class InputManager;
class EntityManager;
class Entity;
class Mix_Chunk;

enum GameState {
    NO_GAME,
    MENU,
    IN_GAME,
    PAUSE_MENU,
    END_GAME
};

class Game {
    Config* cfg;
    Media* gfx;
    InputManager* event;
    EntityManager* manager;

    Time time_a;
    Time time_b;

    Mix_Chunk* clearSFX;
    Mix_Chunk* fallSFX;

public:
    GameState state;
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

    void triggerClearSFX();
    void triggerFallSFX();

    Media* getGFX() const;
    InputManager* getEvent() const;
    Config* getCFG() const;

    void executeCommand(std::shared_ptr<Command> command);
};

#endif
