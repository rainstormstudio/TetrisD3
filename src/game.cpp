#include "game.hpp"
#include "debug.hpp"
#include "config.hpp"
#include "media.hpp"
#include "inputManager.hpp"
#include "math.hpp"
#include "command.hpp"
#include "./EC_Core/entityManager.hpp"
#include "./EC_Core/entity.hpp"
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
    Mix_FreeChunk(clearSFX);
    Mix_FreeChunk(fallSFX);
    clearSFX = nullptr;
    fallSFX = nullptr;
    delete manager;
    delete event;
    delete gfx;
    delete cfg;
}

bool Game::loop() const { return state != NO_GAME; }

Entity* Game::createTetro(double speed) {
    Entity* tetro = manager->addEntity("tetro", Layer::OBJECTS); {
        tetro->addComponent<Transform>();
        tetro->addComponent<Tetromino>();
        tetro->addComponent<Appearance>("./assets/txt/tetrominoes.txt");
        tetro->addComponent<Control>();
        tetro->addComponent<Collider>();
        tetro->addComponent<Gravity>(speed);
    }
    return tetro;
}

void Game::init() {
    Debug::enabled = true;
    Debug::msg("Game::init start");
    cfg = new Config("./config/config.txt");
    Debug::msg("cfg constructed", 1);
    gfx = new Media("Line of Fire", cfg->tilesetPath, 16, 16, 0, cfg->fontPath, cfg->screenWidth, cfg->screenHeight, 30, 40);
    Debug::msg("gfx constructed", 1);
    event = new InputManager(cfg);
    Debug::msg("event constructed", 1);
    manager = new EntityManager(this);
    Debug::msg("manager constructed", 1);
    clearSFX = Mix_LoadWAV("./assets/audio/clear.wav");
    if (!clearSFX) std::cerr << "Failed to load sound effect: SDL_mixer Error: " << Mix_GetError() << std::endl;
    fallSFX = Mix_LoadWAV("./assets/audio/fall.wav");
    if (!fallSFX) std::cerr << "Failed to load sound effect: SDL_mixer Error: " << Mix_GetError() << std::endl;

    Entity* gameField = manager->addEntity("Playfield", Layer::MAP); {
        gameField->addComponent<GameField>(0);
        gameField->addComponent<Transform>(12, 4);
        if (!cfg->mute_music)
            gameField->addComponent<Music>("./assets/audio/theme.wav");
    }

    Entity* interface = manager->addEntity("Interface", Layer::UI); {
        interface->addComponent<Transform>(7, 4);
        interface->addComponent<Appearance>("./assets/txt/UI.txt", 0, 0, 26, 22);
        interface->addComponent<Panel>();
    }

    state = IN_GAME;
    Debug::msg("Game::init done");
    Debug::line();

    time_a = std::chrono::high_resolution_clock::now();
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
            break;
        }
        case IN_GAME: {
            event->update();
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
            if (event->input[QUIT]) {
                state = NO_GAME;
            } else if (event->input[PAUSE]) {
                setPause();
            }
            break;
        }
        case END_GAME: {
            // TODO: restart menu, etc
            state = NO_GAME;
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
            break;
        }
        case IN_GAME: {
            gfx->clear();
            manager->renderByLayer(Layer::MAP);
            manager->renderByLayer(Layer::OBJECTS);
            manager->renderByLayer(Layer::UI);
            gfx->render();
            break;
        }
        case PAUSE_MENU: {
            gfx->clear();
            manager->render();
            gfx->render();
            break;
        }
        case END_GAME: {
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
    } else if (state == PAUSE_MENU) {
        state = IN_GAME;
    }
}

void Game::triggerClearSFX() {
    if (cfg->mute_sfx) return;
    Mix_PlayChannel(-1, clearSFX, 0);
}

void Game::triggerFallSFX() {
    if (cfg->mute_sfx) return;
    Mix_PlayChannel(-1, fallSFX, 0);
}

Media* Game::getGFX() const { return gfx; }

InputManager* Game::getEvent() const { return event; }

Config* Game::getCFG() const { return cfg; }

void Game::executeCommand(std::shared_ptr<Command> command) {
    command->execute();
}
