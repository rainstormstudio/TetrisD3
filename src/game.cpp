#include "game.hpp"
#include "debug.hpp"
#include "config.hpp"
#include "saves.hpp"
#include "media.hpp"
#include "inputManager.hpp"
#include "math.hpp"
#include "command.hpp"
#include "menu.hpp"
#include "backgroundEffect.hpp"
#include "./EC_Core/entityManager.hpp"
#include "./EC_Core/entity.hpp"
#include "./EC_Core/componentList.hpp"

Game::Game() {
    state = NO_GAME;
    cfg = nullptr;
    saves = nullptr;
    gfx = nullptr;
    event = nullptr;
    manager = nullptr;
    menu = nullptr;
    bg = nullptr;
    Math::initRandom();
}

Game::~Game() {
    if (manager)
        manager->destroy();
    Mix_FreeChunk(clearSFX);
    Mix_FreeChunk(fallSFX);
    clearSFX = nullptr;
    fallSFX = nullptr;
    delete bg;
    delete menu;
    delete manager;
    delete event;
    delete gfx;
    delete saves;
    delete cfg;
}

bool Game::loop() const { return state != NO_GAME; }

void Game::createLevel() {
    manager = new EntityManager(this);
    Debug::msg("manager constructed", 1);
    Entity* gameField = manager->addEntity("Playfield", Layer::MAP); {
        gameField->addComponent<GameField>(0);
        gameField->addComponent<Transform>(12, 2);
        gameField->addComponent<Music>(cfg->musicPath);
        gameField->addComponent<SoundEffects>(
            cfg->rotateSFXPath,
            cfg->softdropSFXPath,
            cfg->harddropSFXPath,
            cfg->clearsingleSFXPath,
            cfg->cleardoubleSFXPath,
            cfg->cleartripleSFXPath,
            cfg->cleartetrisSFXPath,
            cfg->levelupSFXPath,
            cfg->gameoverSFXPath
        );
    }

    Entity* interface = manager->addEntity("Interface", Layer::UI); {
        interface->addComponent<Transform>(7, 2);
        interface->addComponent<Appearance>(cfg->UIPath, 0, 0, 26, 22);
        interface->addComponent<Panel>();
    }

    state = IN_GAME;

    time_a = std::chrono::high_resolution_clock::now();
}

Entity* Game::createTetro(double speed) {
    Entity* tetro = manager->addEntity("tetro", Layer::OBJECTS); {
        tetro->addComponent<Transform>();
        tetro->addComponent<Tetromino>();
        tetro->addComponent<Appearance>(cfg->tetroPath);
        tetro->addComponent<Control>();
        tetro->addComponent<Collider>();
        tetro->addComponent<Gravity>(speed);
    }
    return tetro;
}

void Game::endLevel() {
    Debug::enabled = false;
    Debug::msg("start destroying manager");
    if (manager)
        manager->destroy();
    delete manager;
    manager = nullptr;
    Debug::msg("end destroying manager");
    Debug::line();
    state = MENU;
    Debug::msg("endLevel done");
}

void Game::init() {
    Debug::enabled = false;
    Debug::msg("Game::init start");
    cfg = new Config("./config/config.txt");
    Debug::msg("cfg constructed", 1);
    saves = new Saves(cfg->savePath);
    Debug::msg("saves constructed", 1);
    gfx = new Media("TetrisD3", cfg->tilesetPath, 16, 16, cfg->getFullscreenFlag(), cfg->fontPath, cfg->screenWidth, cfg->screenHeight, 26, 40);
    Debug::msg("gfx constructed", 1);
    event = new InputManager(cfg, gfx);
    Debug::msg("event constructed", 1);
    menu = new Menu(this, cfg->titlePath, cfg->softdropSFXPath, {0, 0, 17, 10}, {12, 2, 17, 10});
    Debug::msg("menu constructed", 1);
    bg = new BackgroundEffect(this, {0, 0, 40, 26});

    Debug::msg("Game::init done");
    Debug::line();

    state = MENU;
}

void Game::update() {
    time_b = std::chrono::high_resolution_clock::now();
    Debug::enabled = false;
    Debug::msg("update start");
    switch (state) {
        case NO_GAME: {
            break;
        }
        case MENU: {
            Debug::enabled = false;
            event->update();
            bg->update();
            menu->update();

            if (event->input[QUIT]) {
                state = NO_GAME;
            }
            Debug::enabled = false;
            break;
        }
        case IN_GAME: {
            event->update();
            bg->update();
            Debug::msg("update MAP");
            manager->updateByLayer(Layer::MAP);
            manager->updateByLayer(Layer::UI);
            Debug::msg("update MAP done");
            if (event->input[QUIT]) {
                state = NO_GAME;
            } else if (event->input[PAUSE]) {
                setPause();
            }
            break;
        }
        case PAUSE_MENU: {
            event->update();
            menu->update();
            if (event->input[QUIT]) {
                state = NO_GAME;
            }
            break;
        }
        case END_GAME: {
            event->update();
            bg->update();
            menu->update();
            if (event->input[QUIT]) {
                state = NO_GAME;
            }
            break;
        }
    }
    time_a = time_b;
    Debug::msg("update end");
    Debug::line();
}

void Game::render() {
    Debug::enabled = false;
    Debug::msg("Game::render start");
    switch (state) {
        case NO_GAME: {
            break;
        }
        case MENU: {
            gfx->clear();
            bg->render(0.2, 0.5, 0.5);
            menu->render();
            gfx->render();
            break;
        }
        case IN_GAME: {
            gfx->clear();
            bg->render(1.0, 1.0, 1.0);
            manager->renderByLayer(Layer::MAP);
            manager->renderByLayer(Layer::OBJECTS);
            manager->renderByLayer(Layer::UI);
            gfx->render();
            break;
        }
        case PAUSE_MENU: {
            gfx->clear();
            manager->render();
            gfx->addFilter(0.3);
            menu->render();
            gfx->render();
            break;
        }
        case END_GAME: {
            gfx->clear();
            bg->render(0.0, 0.5, 0.5);
            menu->render();
            gfx->render();
            break;
        }
    }
    Debug::msg("Game::render done");
}

double Game::getDeltaTime() const {
    double deltatime = std::chrono::duration_cast<std::chrono::microseconds>(time_b - time_a).count() / 1000000.0f;
    return deltatime;
}

void Game::setPause() {
    Entity* gamefield = manager->getEntityByName("Playfield");
    Music* music = gamefield->getComponent<Music>();
    music->pauseMusic();
    if (state == IN_GAME) {
        state = PAUSE_MENU;
        menu->state = Menu::PAUSE_MENU;
    } else if (state == PAUSE_MENU) {
        state = IN_GAME;
    }
}

Media* Game::getGFX() const { return gfx; }

InputManager* Game::getEvent() const { return event; }

EntityManager* Game::getEntityManager() const { return manager; }

Menu* Game::getMenu() const { return menu; }

Config* Game::getCFG() const { return cfg; }

Saves* Game::getSaves() const { return saves; }

void Game::executeCommand(std::shared_ptr<Command> command) {
    command->execute();
}
