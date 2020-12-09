#include "panel.hpp"
#include "transform.hpp"
#include "gravity.hpp"
#include "gamefield.hpp"
#include "../../media.hpp"
#include "../../texture.hpp"
#include "../../debug.hpp"

#include <iomanip>
#include <sstream>

std::string Panel::prefix(int value, int width, char ch) {
    std::string result = "";
    result = std::to_string(value);
    int len = result.length();
    for (int i = 0; i < width - len; i ++) {
        result = ch + result;
    }
    return result;
}

std::string Panel::doubleToString(double value, int width, char ch) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << value;
    std::string result = ss.str() + "Ln/s";
    int len = result.length();
    for (int i = 0; i < width - len; i ++) {
        result = ch + result;
    }
    return result;
}

Panel::Panel() {
    score = 0;
    level = 0;
    totallines = 0;
    lines = 0;
    timepassed = 0;
    active = false;
}

void Panel::setActive(bool value) {
    active = value;
}

void Panel::init() {}

void Panel::addlines(int num) {
    score += points[num] * (level + 1);
    totallines += num;
    lines += num;
    if (lines >= 10) {
        level ++;
        Entity* gamefield = owner->manager.getEntityByName("Playfield");
        GameField* playfield = gamefield->getComponent<GameField>();
        playfield->setSpeed(playfield->getSpeed() * 1.1);
        playfield->triggerLevelup();
        lines = lines % 10;
    }
}

void Panel::update() {
    if (active) 
        timepassed += owner->game->getDeltaTime();
}

void Panel::render() {
    std::vector<CPixel> bar = {
        CPixel{0, 0, 0, 0, 0, 255, 51, 51, 255},
        CPixel{0, 0, 0, 0, 0, 255, 92, 51, 255},
        CPixel{0, 0, 0, 0, 0, 255, 133, 51, 255},
        CPixel{0, 0, 0, 0, 0, 255, 174, 51, 255},
        CPixel{0, 0, 0, 0, 0, 255, 115, 51, 255},
        CPixel{0, 0, 0, 0, 0, 254, 255, 51, 255},
        CPixel{0, 0, 0, 0, 0, 213, 255, 51, 255},
        CPixel{0, 0, 0, 0, 0, 172, 255, 51, 255},
        CPixel{0, 0, 0, 0, 0, 131, 255, 51, 255}
    };
    Transform* transform = owner->getComponent<Transform>();
    Media* gfx = owner->game->getGFX();
    std::vector<int> times = getTime();
    std::string time = prefix(times[0], 2, '0') + ":" + prefix(times[1], 2, '0') + ":" + prefix(times[2], 2, '0');
    gfx->write(time, transform->position.x + 17, transform->position.y + 10, 255, 255, 255, 255, 0, 0, 0, 255);
    gfx->write(prefix(score, 6, ' '), transform->position.x + 17, transform->position.y + 14, 255, 255, 255, 255, 0, 0, 0, 255);
    gfx->write(prefix(level, 6, ' '), transform->position.x + 17, transform->position.y + 16, 255, 255, 255, 255, 0, 0, 0, 255);
    gfx->write(prefix(totallines, 6, ' '), transform->position.x + 17, transform->position.y + 18, 255, 255, 255, 255, 0, 0, 0, 255);
    Entity* gamefield = owner->manager.getEntityByName("Playfield");
    GameField* playfield = gamefield->getComponent<GameField>();
    std::string speed = doubleToString(playfield->getSpeed(), 8, ' ');
    gfx->write(speed, transform->position.x + 17, transform->position.y + 7, 255, 255, 255, 255, 0, 0, 0, 255);
    for (int i = 9 - lines; i < 9; i ++) {
        for (int j = 0; j < 2; j ++) {
            CPixel* info = new CPixel(bar[i]);
            gfx->drawPoint(info, transform->position.x + j + 3, transform->position.y + i + 12);
            delete info;
        }
    }
}

std::vector<int> Panel::getTime() {
    double temp = timepassed;
    int hours = temp / 3600.0;
    temp -= hours * 3600.0;
    int minutes = temp / 60.0;
    temp -= minutes * 60.0;
    int seconds = temp;
    std::vector<int> time(3, 0);
    time[0] = hours;
    time[1] = minutes;
    time[2] = seconds;
    return time;
}