#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include "inputManager.hpp"

class Config {
    std::string trim(std::string str);
public:
    std::string tilesetPath;
    std::string fontPath;
    unsigned int screenWidth;
    unsigned int screenHeight;
    bool mute_music;
    bool mute_sfx;
    std::vector<std::string> input;

    Config(std::string filename);
};

#endif
