#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "../entityManager.hpp"
#include <vector>

class Tetromino : public Component {
    const std::vector<SDL_Rect> typeInfo = {
        {0, 0, 4, 4},
        {0, 4, 3, 3},
        {0, 7, 3, 3},
        {0, 10, 4, 3},
        {0, 13, 3, 3},
        {0, 16, 3, 3},
        {0, 19, 3, 3}
    };
    int direction;
    SDL_Rect src;
    SDL_Rect target;
    int rowIndex;
    int colIndex;
    bool hold;

public:
    enum TetroType {
        TETRO_I = 0,
        TETRO_J,
        TETRO_L,
        TETRO_O,
        TETRO_S,
        TETRO_T,
        TETRO_Z
    };
    TetroType type;

    Tetromino();

    ~Tetromino() override;

    void setHold(bool flag);

    void rotateRight();

    void rotateLeft();

    void moveRight();

    void moveLeft();

    void moveDown();

    void harddrop();

    void init() override;

    void update() override;

    void render() override;
};

#endif
