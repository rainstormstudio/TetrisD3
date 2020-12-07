#include "gamefield.hpp"
#include "tetromino.hpp"
#include "transform.hpp"
#include "panel.hpp"
#include "soundeffects.hpp"
#include "../../game.hpp"
#include "../../EC_Core/entityManager.hpp"
#include "../../texture.hpp"
#include "../../media.hpp"
#include "../../debug.hpp"

GameField::GameField(int preoccupiedrows) : preoccupiedrows{preoccupiedrows}  {
    playfield = std::vector<std::vector<Cell>>(rows);
    for (int i = 0; i < rows; i ++) {
        playfield[i] = std::vector<Cell>(cols);
        for (int j = 0; j < cols; j ++) {
            playfield[i][j] = {false, ' ', 0, 0, 0, 255, 0, 0, 0, 255};
        }
    }
    clearSpeed = 30.0;
    clearProcess = 0.0;
    clearCol = 0;
    airflow = 0.0;
    airflowprocess = 0.0;
    airspeed = 50.0;
    air = {0, 0, 3, 4};
    currentTetro = nullptr;
    nextTetro = nullptr;
    speed = 1.0;
    levelup = 0;
    levelupprocess = 0.0;
}

bool GameField::isOccupied(int row, int col) {
    if (0 <= row && row < rows && 0 <= col && col < cols)
        return playfield[row][col].occupied;    
    else 
        return true;
}

void GameField::occupy(int row, int col, CPixel* info) {
    if (!(0 <= row && row < rows && 0 <= col && col < cols)) return;
    if (!info) return;
    CPixel* transparent = new CPixel();
    if (*info != *transparent) {
        playfield[row][col].occupied = true;
        playfield[row][col].ch = info->ch;
        playfield[row][col].r = info->r;
        playfield[row][col].g = info->g;
        playfield[row][col].b = info->b;
        playfield[row][col].a = info->a;
        playfield[row][col].br = info->br;
        playfield[row][col].bg = info->bg;
        playfield[row][col].bb = info->bb;
        playfield[row][col].ba = info->ba;
    }
    delete transparent;
}

void GameField::checklines() {
    for (int i = 0; i < rows; i ++) {
        bool flag = true;
        for (int j = 0; j < cols; j ++) {
            if (!playfield[i][j].occupied) {
                flag = false;
                break;
            }
        }
        if (flag) {
            lines.push_back(i);
        }
    }
    if (!lines.empty()) {
        clearCol = cols / 2;
        Entity* gamefield = owner->manager.getEntityByName("Playfield");
        SoundEffects* sfx = gamefield->getComponent<SoundEffects>();
        if (lines.size() == 1) {
            sfx->triggerSingle();
        } else if (lines.size() == 2) {
            sfx->triggerDouble();
        } else if (lines.size() == 3) {
            sfx->triggerTriple();
        } else if (lines.size() == 4) {
            sfx->triggerTetris();
        }
    }
}

void GameField::clearlines() {
    double deltatime = owner->game->getDeltaTime();
    clearProcess += clearSpeed * deltatime;
    if (clearProcess >= 1.0) {
        clearCol --;
        if (clearCol < 0) {
            droplines();
            return;
        }
        for (int j = 0; j < lines.size(); j ++) {
            int row = lines[j];
            int col = clearCol;
            playfield[row][col] = {false, ' ', 0, 0, 0, 255, 0, 0, 0, 255};
            playfield[row][cols - col - 1] = {false, ' ', 0, 0, 0, 255, 0, 0, 0, 255};
        }
        clearProcess = 0.0;
    }
}

void GameField::droplines() {
    for (auto row : lines) {
        for (int i = row - 1; i >= 0; i --) {
            for (int j = 0; j < cols; j ++) {
                playfield[i + 1][j] = playfield[i][j];
            }
        }
    }
    Entity* interface = owner->manager.getEntityByName("Interface");
    Panel* panel = interface->getComponent<Panel>();
    panel->addlines(lines.size());
    lines.clear();
}

void GameField::triggerAirflow(int row, int col, int width) {
    air.x = col;
    air.y = row - 3;
    air.w = width;
    airflow = 1.0;
}

void GameField::triggerLevelup() {
    levelup = 10;
    levelupprocess = 0.0;
}

void GameField::init() {
    for (int i = 0; i < preoccupiedrows; i ++) {
        for (int j = 0; j < cols; j ++) {
            playfield[rows - 1 - i][j] = {true, 20, 255, 255, 255, 240, 255, 255, 255, 155};
        }
    }

    currentTetro = owner->game->createTetro(1.0);
    Tetromino* tetromino = currentTetro->getComponent<Tetromino>();
    tetromino->setHold(true);
    nextTetro = owner->game->createTetro(1.0);
}

void GameField::update() {
    double deltatime = owner->game->getDeltaTime();
    if (airflow > 0.0) {
        airflowprocess += airspeed * deltatime;
        if (airflowprocess > 1.0) {
            air.y --;
            airflowprocess = 0.0;
            airflow -= 0.1;
        }
    }
    if (levelup > 0) {
        levelupprocess += 10.0 * deltatime;
        if (levelupprocess > 1.0) {
            levelup --;
            levelupprocess = 0.0;
        }
    }
    if (lines.empty()) {
        owner->manager.updateByLayer(Layer::OBJECTS);
        std::vector<Entity*> tetros = owner->manager.getEntitiesByLayer(Layer::OBJECTS);
        if (tetros.size() < 2) {
            currentTetro = nextTetro;
            Tetromino* tetromino = currentTetro->getComponent<Tetromino>();
            tetromino->setHold(true);
            nextTetro = owner->game->createTetro(speed);
        }
        checklines();
        if (lines.empty()) {
            bool lost = false;
            for (int i = 0; i < cols; i ++) {
                if (playfield[19][i].occupied) {
                    lost = true;
                    break;
                }
            }
            if (lost) {
                owner->game->state = END_GAME;
            }
        }
    } else {
        clearlines();
    }
}

void GameField::render() {
    Media* gfx = owner->game->getGFX();
    Transform* transform = owner->getComponent<Transform>();
    for (int i = rows - 1; i >= rows - 1 - 20; i --) {
        for (int j = 0; j < cols; j ++) {
            CPixel* cell = new CPixel{
                    playfield[i][j].ch,
                    playfield[i][j].r,
                    playfield[i][j].g,
                    playfield[i][j].b,
                    playfield[i][j].a,
                    playfield[i][j].br,
                    playfield[i][j].bg,
                    playfield[i][j].bb,
                    playfield[i][j].ba
                };
            gfx->drawPoint(
                cell, 
                round(j + transform->position.x + 1), 
                round(i - rows + 21 + transform->position.y));
            delete cell;
        }
    }
    if (airflow > 0.0) {
        for (int i = 0; i < air.h; i ++) {
            for (int j = 0; j < air.w; j ++) {
                CPixel* cell = new CPixel{
                    0,
                    0, 0, 0, 255,
                    255, 255, 255, static_cast<Uint8>(200 * airflow)
                };
                gfx->drawPoint(cell, 
                    round(j + transform->position.x + air.x + 1),
                    round(i - rows + 21 + transform->position.y + air.y));
                delete cell;
            }
        }
    }
    if (levelup > 0) {
        if (levelup % 3 == 2) {
            gfx->write("LE", transform->position.x - 2, transform->position.y + 7, 255, 255, 255, 255, 255, 0, 0, 255);
            gfx->write("VE", transform->position.x - 2, transform->position.y + 8, 255, 255, 255, 255, 255, 128, 0, 255);
            gfx->write("L ", transform->position.x - 2, transform->position.y + 9, 255, 255, 255, 255, 255, 255, 0, 255);
            gfx->write("UP", transform->position.x - 2, transform->position.y + 10, 255, 255, 255, 255, 255, 0, 0, 255);
        } else if (levelup % 3 == 1) {
            gfx->write("LE", transform->position.x - 2, transform->position.y + 7, 255, 255, 255, 255, 255, 128, 0, 255);
            gfx->write("VE", transform->position.x - 2, transform->position.y + 8, 255, 255, 255, 255, 255, 255, 0, 255);
            gfx->write("L ", transform->position.x - 2, transform->position.y + 9, 255, 255, 255, 255, 255, 0, 0, 255);
            gfx->write("UP", transform->position.x - 2, transform->position.y + 10, 255, 255, 255, 255, 255, 128, 0, 255);
        } else {
            gfx->write("LE", transform->position.x - 2, transform->position.y + 7, 255, 255, 255, 255, 255, 255, 0, 255);
            gfx->write("VE", transform->position.x - 2, transform->position.y + 8, 255, 255, 255, 255, 255, 0, 0, 255);
            gfx->write("L ", transform->position.x - 2, transform->position.y + 9, 255, 255, 255, 255, 255, 128, 0, 255);
            gfx->write("UP", transform->position.x - 2, transform->position.y + 10, 255, 255, 255, 255, 255, 255, 0, 255);
        }
    }
}