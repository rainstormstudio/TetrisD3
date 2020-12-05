#ifndef GAMEFIELD_HPP
#define GAMEFIELD_HPP

#include "../entityManager.hpp"

struct CPixel;
class Entity;

class GameField : public Component {
    const int rows = 40;
    const int cols = 10;
    struct Cell {
        bool occupied;
        Uint8 ch;
        Uint8 r, g, b, a;
        Uint8 br, bg, bb, ba;
    };

    int preoccupiedrows;
    std::vector<std::vector<Cell>> playfield;
    std::vector<int> lines;
    int clearCol;
    double clearSpeed;
    double clearProcess;
    Entity* currentTetro;
    Entity* nextTetro;

public:
    GameField(int preoccupiedrows);

    bool isOccupied(int row, int col);

    void occupy(int row, int col, CPixel* info);

    void checklines();

    void clearlines();

    void droplines();

    void init() override;

    void update() override;

    void render() override;

    ~GameField() override {}
};

#endif
