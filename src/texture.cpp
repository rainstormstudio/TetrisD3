#include "texture.hpp"
#include <fstream>
#include <iostream>

Texture::Texture(std::string filename) {
    this->filename = "";
    numRows = 60;
    numCols = 60;
    cpixels = std::vector<std::vector<CPixel>>(numRows);
    for (int i = 0; i < numRows; ++i) {
        cpixels[i] = std::vector<CPixel>(numCols);
        for (int j = 0; j < numCols; ++j) {
            cpixels[i][j] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        }
    }
    importTxt(filename);
}

void Texture::importTxt(std::string filename) {
    if (filename == "") {
        return;
    }
    std::ifstream infile{filename};
    if (infile.is_open()) {
        this->filename = filename;
        std::string line;
        int row = 0;
        while (std::getline(infile, line)) {
            int len = line.length();
            int col = 0;
            int index = 0;
            Uint8 info[9];
            std::string token = "";
            for (int i = 0; i < len; ++i) {
                if (line[i] == '(') {
                    index = 0;
                    token = "";
                } else if (line[i] == ')') {
                    info[index] = static_cast<Uint8>(std::stoi(token));
                    cpixels[row][col] = {info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7], info[8]};
                    ++col;
                } else if (line[i] == ',') {
                    info[index] = static_cast<Uint8>(std::stoi(token));
                    token = "";
                    ++index;
                } else if (line[i] >= '0' && line[i] <= '9') {
                    token += line[i];
                } else {
                    std::cerr << "Error reading file: " << filename << std::endl;
                    break;
                }
            }
            ++row;
        }
        infile.close();
    } else {
        std::cerr << "Unable to open " << filename << std::endl;
    }
}

unsigned int Texture::getWidth() const { return numCols; }

unsigned int Texture::getHeight() const { return numRows; }

std::string Texture::getFilename() const { return filename; }

CPixel Texture::getInfo(int x, int y) const {
    if (x >= 0 && x < numCols
        && y >= 0 && y < numRows) {
        return cpixels[y][x];
    } else {
        return {0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
}
