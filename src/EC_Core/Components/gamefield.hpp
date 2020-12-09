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

    double airflow;
    double airflowprocess;
    double airspeed;
    SDL_Rect air;

    int levelup;
    double levelupprocess;

    Entity* currentTetro;
    Entity* nextTetro;
    double speed;

    bool lost;

    bool active;

public:
    GameField(int preoccupiedrows);

    void getStart();

    bool isOccupied(int row, int col);

    void occupy(int row, int col, CPixel* info);

    void checklines();

    void clearlines();

    void droplines();

    void triggerAirflow(int row, int col, int width);

    void triggerLevelup();

    double getSpeed() const {
        return speed;
    }

    void setSpeed(double value) {
        speed = value;
    }

    void clearField();

    void init() override;

    void update() override;

    void render() override;

    ~GameField() override {}
};

#endif
