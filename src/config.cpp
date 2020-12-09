#include "config.hpp"
#include "media.hpp"
#include "math.hpp"
#include "debug.hpp"
#include <fstream>
#include <iostream>

std::string Config::comment(const std::string content) {
    return "# " + content;
}

std::string Config::item(std::string tag, std::string value) {
    return tag + "=" + value;
}

std::string Config::item(std::string tag, unsigned int value) {
    return item(tag, std::to_string(value));
}

std::string Config::item(std::string tag, bool value) {
    std::string boolean;
    if (value) {
        boolean = "TRUE";
    } else {
        boolean = "FALSE";
    }
    return item(tag, boolean);
}

std::string Config::trim(std::string str) {
    const auto begin = str.find_first_not_of(' ');
    if (begin == std::string::npos) {
        return "";
    }
    const auto end = str.find_last_not_of(' ');
    const auto range = end - begin + 1;

    return str.substr(begin, range);
}

Config::Config(std::string filename) {
    configFilePath = filename;
    // defaults
    savePath = "./save/scores.txt";
    tilesetPath = "./assets/tilesets/TetrisD3tileset.png";
    fontPath = "./assets/fonts/Monaco.ttf";
    titlePath = "./assets/txt/title.txt";
    UIPath = "./assets/txt/UI.txt";
    tetroPath = "./assets/txt/tetrominoes.txt";
    musicPath = "./assets/audio/theme.wav";
    rotateSFXPath = "./assets/audio/line.wav";
    softdropSFXPath = "";
    harddropSFXPath = "./assets/audio/fall.wav";
    clearsingleSFXPath = "./assets/audio/clear.wav";
    cleardoubleSFXPath = "./assets/audio/clear.wav";
    cleartripleSFXPath = "./assets/audio/clear.wav";
    cleartetrisSFXPath = "./assets/audio/clear.wav";
    levelupSFXPath = "./assets/audio/success.wav";
    gameoverSFXPath = "./assets/audio/gameover.wav";
    screenWidth = 1280;
    screenHeight = 720;
    setFullscreen(false);
    music_volume = 128;
    sfx_volume = 128;
    mute_music = false;
    mute_sfx = false;
    input = std::vector<std::string>(TOTAL_INPUTTYPES);
    input[MOVEUP] = "W";
    input[MOVEDOWN] = "S";
    input[MOVELEFT] = "A";
    input[MOVERIGHT] = "D";
    input[ROTATE_RIGHT] = "W";
    input[ROTATE_LEFT] = "Q";
    input[DROP] = "Space";
    input[PAUSE] = "Return";
    input[CONFIRM] = "Return";

    if (filename == "") {
        return;
    }

    std::ifstream infile{filename};
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            if (line == "") continue;
            int len = line.length();
            std::string tag = "";
            std::string value = "";
            bool flag = false;
            for (int i = 0; i < len; ++i) {
                if (line[i] == '#') {
                    break;
                } else if (line[i] == '=') {
                    flag = true;
                } else {
                    if (flag) {
                        value += line[i];
                    } else {
                        tag += line[i];
                    }
                }
            }
            tag = trim(tag);
            value = trim(value);
            if (tag == "SAVE") {
                savePath = value;
            } else if (tag == "TILESET") {
                tilesetPath = value;
            } else if (tag == "FONT") {
                fontPath = value;
            } else if (tag == "TITLE") {
                titlePath = value;
            } else if (tag == "UI") {
                UIPath = value;
            } else if (tag == "TETROMINOES") {
                tetroPath = value;
            } else if (tag == "MUSIC") {
                musicPath = value;
            } else if (tag == "ROTATE_SFX") {
                rotateSFXPath = value;
            } else if (tag == "SOFTDROP_SFX") {
                softdropSFXPath = value;
            } else if (tag == "HARDDROP_SFX") {
                harddropSFXPath = value;
            } else if (tag == "CLEARSINGLE_SFX") {
                clearsingleSFXPath = value;
            } else if (tag == "CLEARDOUBLE_SFX") {
                cleardoubleSFXPath = value;
            } else if (tag == "CLEARTRIPLE_SFX") {
                cleartripleSFXPath = value;
            } else if (tag == "CLEARTETRIS_SFX") {
                cleartetrisSFXPath = value;
            } else if (tag == "LEVELUP_SFX") {
                levelupSFXPath = value;
            } else if (tag == "GAMEOVER_SFX") {
                gameoverSFXPath = value;
            } else if (tag == "SCREENWIDTH" && Math::isNat(value)) {
                screenWidth = std::stoi(value);
            } else if (tag == "SCREENHEIGHT" && Math::isNat(value)) {
                screenHeight = std::stoi(value);
            } else if (tag == "FULLSCREEN") {
                if (value == "TRUE") {
                    setFullscreen(true);
                } else {
                    setFullscreen(false);
                }
            } else if (tag == "MUTE_MUSIC") {
                if (value == "TRUE") {
                    mute_music = true;
                }
            } else if (tag == "MUSIC_VOLUME" && Math::isNat(value)) {
                int temp = std::stoi(value);
                if (0 <= temp && temp <= 128) {
                    music_volume = temp;
                }
            } else if (tag == "MUTE_SFX") {
                if (value == "TRUE") {
                    mute_sfx = true;
                }
            } else if (tag == "SFX_VOLUME" && Math::isNat(value)) {
                int temp = std::stoi(value);
                if (0 <= temp && temp <= 128) {
                    sfx_volume = temp;
                }
            } else if (tag == "UP") {
                input[MOVEUP] = value;
            } else if (tag == "DOWN") {
                input[MOVEDOWN] = value;
            } else if (tag == "LEFT") {
                input[MOVELEFT] = value;
            } else if (tag == "RIGHT") {
                input[MOVERIGHT] = value;
            } else if (tag == "ROTATE_RIGHT") {
                input[ROTATE_RIGHT] = value;
            } else if (tag == "ROTATE_LEFT") {
                input[ROTATE_LEFT] = value;
            } else if (tag == "DROP") {
                input[DROP] = value;
            } else if (tag == "PAUSE") {
                input[PAUSE] = value;
            } else if (tag == "CONFIRM") {
                input[CONFIRM] = value;
            }
        }
        infile.close();
        saveToFile();
    } else {
        saveToFile();
    }
}

void Config::setFullscreen(bool value) {
    fullscreen = value;
    if (fullscreen) {
        fullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else {
        fullscreenFlag = 0;
    }
}

bool Config::isFullscreen() const {
    return fullscreen;
}

Uint32 Config::getFullscreenFlag() const {
    return fullscreenFlag;
}

void Config::saveToFile() {
    Debug::enabled = false;
    std::ofstream output(configFilePath);
    if (output.is_open()) {
        output << comment("save path") << std::endl;
        output << item("SAVE", savePath) << std::endl;
        output << std::endl;

        output << comment("graphics") << std::endl;
        output << item("TILESET", tilesetPath) << std::endl;
        output << item("UI", UIPath) << std::endl;
        output << item("TETROMINOES", tetroPath) << std::endl;
        output << std::endl;

        output << comment("sound") << std::endl;
        output << item("MUSIC", musicPath) << std::endl;
        output << item("ROTATE_SFX", rotateSFXPath) << std::endl;
        output << item("SOFTDROP_SFX", softdropSFXPath) << std::endl;
        output << item("HARDDROP_SFX", harddropSFXPath) << std::endl;
        output << item("CLEARSINGLE_SFX", clearsingleSFXPath) << std::endl;
        output << item("CLEARDOUBLE_SFX", cleardoubleSFXPath) << std::endl;
        output << item("CLEARTRIPLE_SFX", cleartripleSFXPath) << std::endl;
        output << item("CLEARTETRIS_SFX", cleartetrisSFXPath) << std::endl;
        output << item("LEVELUP_SFX", levelupSFXPath) << std::endl;
        output << item("GAMEOVER_SFX", gameoverSFXPath) << std::endl;
        output << std::endl;

        output << comment("window info") << std::endl;
        output << item("FULLSCREEN", fullscreen) << std::endl;
        output << item("SCREENWIDTH", screenWidth) << std::endl;
        output << item("SCREENHEIGHT", screenHeight) << std::endl;
        output << std::endl;

        output << comment("music settings") << std::endl;
        output << comment("volume range: 0 - 128") << std::endl;
        output << item("MUTE_MUSIC", mute_music) << std::endl;
        output << item("MUSIC_VOLUME", static_cast<unsigned int>(music_volume)) << std::endl;
        output << item("MUTE_SFX", mute_sfx) << std::endl;
        output << item("SFX_VOLUME", static_cast<unsigned int>(sfx_volume)) << std::endl;
        output << std::endl;

        output << comment("key configs") << std::endl;
        output << comment("use SDL key names") << std::endl;
        output << item("UP", input[MOVEUP]) << std::endl;
        output << item("DOWN", input[MOVEDOWN]) << std::endl;
        output << item("LEFT", input[MOVELEFT]) << std::endl;
        output << item("RIGHT", input[MOVERIGHT]) << std::endl;
        output << item("ROTATE_RIGHT", input[ROTATE_RIGHT]) << std::endl;
        output << item("ROTATE_LEFT", input[ROTATE_LEFT]) << std::endl;
        output << item("DROP", input[DROP]) << std::endl;
        output << item("PAUSE", input[PAUSE]) << std::endl;
        output << item("CONFIRM", input[CONFIRM]) << std::endl;
        output << std::endl;

        output.close();
    } else {
        std::cerr << "Failed to open config file: " << configFilePath << std::endl;
    }
    Debug::enabled = false;
}