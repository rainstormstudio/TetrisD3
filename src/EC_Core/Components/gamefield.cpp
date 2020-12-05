#include "gamefield.hpp"
#include "transform.hpp"
#include "../../game.hpp"
#include "../../EC_Core/entityManager.hpp"
#include "../../texture.hpp"
#include "../../graphics.hpp"
#include "../../debug.hpp"

GameField::GameField(int preoccupiedrows) : preoccupiedrows{preoccupiedrows}  {
    playfield = std::vector<std::vector<Cell>>(rows);
    for (int i = 0; i < rows; i ++) {
        playfield[i] = std::vector<Cell>(cols);
        for (int j = 0; j < cols; j ++) {
            playfield[i][j] = {false, ' ', 0, 0, 0, 255, 0, 0, 0, 255};
        }
    }
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

void GameField::init() {
    for (int i = 0; i < preoccupiedrows; i ++) {
        for (int j = 0; j < cols; j ++) {
            playfield[rows - 1 - i][j] = {true, 20, 255, 255, 255, 240, 255, 255, 255, 155};
        }
    }

    owner->game->createTetro();
}

void GameField::update() {
    Entity* tetro = owner->manager.getEntityByName("tetro");
    if (!tetro) {
        owner->game->createTetro();
    }
}

void GameField::render() {
    Graphics* gfx = owner->game->getGFX();
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
}