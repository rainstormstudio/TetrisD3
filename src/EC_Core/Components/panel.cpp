#include "panel.hpp"
#include "transform.hpp"
#include "../../media.hpp"
#include "../../texture.hpp"
#include "../../debug.hpp"

std::string Panel::prefix(int value, int width, char ch) {
    std::string result = "";
    result = std::to_string(value);
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
}

void Panel::init() {
}

void Panel::addlines(int num) {
    score += points[num] * (level + 1);
    totallines += num;
    lines += num;
    if (lines >= 10) {
        level ++;
        lines = lines % 10;
    }
}

void Panel::update() {
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
    int hours = timepassed / 3600.0;
    timepassed -= hours * 3600.0;
    int minutes = timepassed / 60.0;
    timepassed -= minutes * 60.0;
    int seconds = timepassed;
    std::string time = prefix(hours, 2, '0') + ":" + prefix(minutes, 2, '0') + ":" + prefix(seconds, 2, '0');
    gfx->write(time, transform->position.x + 17, transform->position.y + 10);
    gfx->write(prefix(score, 6, ' '), transform->position.x + 17, transform->position.y + 14);
    gfx->write(prefix(level, 6, ' '), transform->position.x + 17, transform->position.y + 16);
    gfx->write(prefix(totallines, 6, ' '), transform->position.x + 17, transform->position.y + 18);
    for (int i = 9 - lines; i < 9; i ++) {
        for (int j = 0; j < 2; j ++) {
            CPixel* info = new CPixel(bar[i]);
            gfx->drawPoint(info, transform->position.x + j + 3, transform->position.y + i + 12);
            delete info;
        }
    }
}