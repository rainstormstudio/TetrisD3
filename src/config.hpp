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
    std::string UIPath;
    std::string musicPath;
    std::string rotateSFXPath;
    std::string softdropSFXPath;
    std::string harddropSFXPath;
    std::string clearsingleSFXPath;
    std::string cleardoubleSFXPath;
    std::string cleartripleSFXPath;
    std::string cleartetrisSFXPath;
    unsigned int screenWidth;
    unsigned int screenHeight;
    bool mute_music;
    bool mute_sfx;
    std::vector<std::string> input;

    Config(std::string filename);
};

#endif
