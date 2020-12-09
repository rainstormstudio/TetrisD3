#include "countdown.hpp"
#include "../entityManager.hpp"
#include "transform.hpp"
#include "gamefield.hpp"
#include "music.hpp"
#include "../../math.hpp"

Countdown::Countdown() {
    process = 0.0;
    number = 3;
}

Countdown::~Countdown() {
    Entity* gamefield = owner->manager.getEntityByName("Playfield");
    GameField* playfield = gamefield->getComponent<GameField>();
    Music* music = gamefield->getComponent<Music>();
    playfield->getStart();
    music->getStart();
}

void Countdown::update() {
    double deltatime = owner->game->getDeltaTime();
    process += deltatime;
    if (process > 1.0) {
        number --;
        if (number == -1) {
            owner->destroy();
        }
        process = 0.0;
    }
}

void Countdown::render() {
    Media* gfx = owner->game->getGFX();
    Transform* transform = owner->getComponent<Transform>();
    std::cerr << number << std::endl;
    //gfx->addFilter(0.5);
    for (int row = 0; row < 7; row ++) {
        for (int col = 0; col < gfx->getScreenCols(); col ++) {
            int x = col + transform->position.x;
            int y = row + transform->position.y;
            int a = round(
                        255.0 * 
                        (1.0 / Math::bellCurve(gfx->getScreenCols() / 2.0, 10.0, gfx->getScreenCols() / 2.0)) * 
                        (Math::bellCurve(col, 10.0, gfx->getScreenCols() / 2.0)));
            
            if (row > 0 && row < 6) {
                gfx->addForeColor(0, 0, 0, a, x, y);
                gfx->addBackColor(0, 0, 0, a, x, y);
            } else {
                gfx->addForeColor(200, 128, 0, a, x, y);
                gfx->addBackColor(200, 128, 0, a, x, y);
            }
        }
    }
    int labelRows = label[0].size();
    int labelCols = label[0][0].length();
    for (int row = 0; row < labelRows; row ++) {
        for (int col = 0; col < labelCols; col ++) {
            int x = col + transform->position.x + gfx->getScreenCols() / 2 - labelCols / 2;
            x --;
            int y = row + 1 + transform->position.y;
            int a = round(255 * (1.0 - process));
            if (label[number][row][col] == '#') {
                gfx->addForeColor(200, 50, 0, a, x, y);
                gfx->addBackColor(200, 50, 0, a, x, y);
            }
        }
    }
}