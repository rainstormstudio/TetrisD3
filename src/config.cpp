#include "config.hpp"
#include "math.hpp"
#include <fstream>
#include <iostream>

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
    // defaults
    tilesetPath = "./assets/tilesets/Vintl01.png";
    fontPath = "./assets/fonts/Monaco.ttf";
    screenWidth = 800;
    screenHeight = 600;
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
            if (tag == "TILESET") {
                tilesetPath = value;
            } else if (tag == "FONT") {
                fontPath = value;
            } else if (tag == "SCREENWIDTH" && Math::isNat(value)) {
                screenWidth = std::stoi(value);
            } else if (tag == "SCREENHEIGHT" && Math::isNat(value)) {
                screenHeight = std::stoi(value);
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
    } else {
        std::cerr << "Unable to open config file: " << filename << std::endl;
    }
}
