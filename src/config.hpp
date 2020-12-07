#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include "inputManager.hpp"

class Config {
    std::string configFilePath;

    std::string comment(std::string content);
    std::string item(std::string tag, std::string value);
    std::string item(std::string tag, unsigned int value);
    std::string item(std::string tag, bool value);
    
    std::string trim(std::string str);

    bool fullscreen;
    Uint32 fullscreenFlag;
public:
    std::string savePath;
    std::string tilesetPath;
    std::string fontPath;
    std::string titlePath;
    std::string UIPath;
    std::string tetroPath;
    std::string musicPath;
    std::string rotateSFXPath;
    std::string softdropSFXPath;
    std::string harddropSFXPath;
    std::string clearsingleSFXPath;
    std::string cleardoubleSFXPath;
    std::string cleartripleSFXPath;
    std::string cleartetrisSFXPath;
    std::string levelupSFXPath;
    std::string gameoverSFXPath;
    unsigned int screenWidth;
    unsigned int screenHeight;

    int music_volume;   // 0 - 128
    int sfx_volume;     // 0 - 128
    bool mute_music;
    bool mute_sfx;
    std::vector<std::string> input;

    Config(std::string filename);
    
    void setFullscreen(bool value);
    bool isFullscreen() const;
    Uint32 getFullscreenFlag() const;

    void saveToFile();
};

#endif
