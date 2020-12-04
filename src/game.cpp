#include "game.hpp"
#include "debug.hpp"
#include "config.hpp"
#include "graphics.hpp"
#include "inputManager.hpp"
#include "math.hpp"
#include "command.hpp"
#include "./EC_Core/entityManager.hpp"
#include "./EC_Core/componentList.hpp"

Game::Game() {
    state = NO_GAME;
    cfg = nullptr;
    gfx = nullptr;
    event = nullptr;
    manager = nullptr;
    Math::initRandom();
}

Game::~Game() {
    delete manager;
    delete event;
    delete gfx;
    delete cfg;
}

bool Game::loop() const { return state != NO_GAME; }

void Game::init() {
    Debug::enabled = false;
    Debug::msg("Game::init start");
    cfg = new Config("./config/config.txt");
    Debug::msg("cfg constructed", 1);
    gfx = new Graphics("Line of Fire", cfg->tilesetPath, 16, 16, 0, cfg->fontPath, cfg->screenWidth, cfg->screenHeight, 30, 40);
    Debug::msg("gfx constructed", 1);
    event = new InputManager(cfg);
    Debug::msg("event constructed", 1);
    manager = new EntityManager(this);
    Debug::msg("manager constructed", 1);

    Entity* gameField = manager->addEntity("gameField", Layer::OBJECTS); {
        gameField->addComponent<Transform>(12, 4);
        gameField->addComponent<Appearance>("./assets/txt/border.txt", 0, 0, 12, 22);
    }

    state = IN_GAME;
    Debug::msg("Game::init done");
    Debug::line();
}

void Game::update() {
    Debug::enabled = false;
    Debug::msg("Game::update start");
    switch (state) {
        case NO_GAME: {
            break;
        }
        case MENU: {
            break;
        }
        case IN_GAME: {
            event->update();
            if (event->input[QUIT]) {
                state = NO_GAME;
            }
            break;
        }
        case PAUSE_MENU: {
            break;
        }
    }
    Debug::msg("Game::update done");
}

void Game::render() {
    Debug::enabled = false;
    Debug::msg("Game::render start");
    switch (state) {
        case NO_GAME: {
            break;
        }
        case MENU: {
            break;
        }
        case IN_GAME: {
            gfx->clear();
            manager->render();
            gfx->render();
            break;
        }
        case PAUSE_MENU: {
            break;
        }
    }
    Debug::msg("Game::render done");
}

Graphics* Game::getGFX() const { return gfx; }

InputManager* Game::getEvent() const { return event; }

Config* Game::getCFG() const { return cfg; }

void Game::executeCommand(std::shared_ptr<Command> command) {
    command->execute();
}
