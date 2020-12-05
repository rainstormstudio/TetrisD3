#include "panel.hpp"
#include "transform.hpp"
#include "../../graphics.hpp"
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
    start_time = std::chrono::high_resolution_clock::now();
    score = 0;
    level = 0;
    lines = 0;
}

void Panel::init() {
    start_time = std::chrono::high_resolution_clock::now();
    score = 0;
    level = 0;
    lines = 0;
}

void Panel::addlines(int num) {
    score += points[num] * (level + 1);
    lines += num;
    if (lines >= 10) {
        level ++;
        lines = lines % 10;
    }
}

void Panel::update() {
    current_time = std::chrono::high_resolution_clock::now();
}

void Panel::render() {
    Transform* transform = owner->getComponent<Transform>();
    Graphics* gfx = owner->game->getGFX();
    double timepassed = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time).count() / 1000000.0f;
    int hours = timepassed / 3600.0;
    timepassed -= hours * 3600.0;
    int minutes = timepassed / 60.0;
    timepassed -= minutes * 60.0;
    int seconds = timepassed;
    std::string time = prefix(hours, 2, '0') + ":" + prefix(minutes, 2, '0') + ":" + prefix(seconds, 2, '0');
    gfx->write(time, transform->position.x + 17, transform->position.y + 10);
    gfx->write(prefix(score, 6, ' '), transform->position.x + 17, transform->position.y + 14);
    gfx->write(prefix(level, 6, ' '), transform->position.x + 17, transform->position.y + 16);
    gfx->write(prefix(lines, 6, ' '), transform->position.x + 17, transform->position.y + 18);
}