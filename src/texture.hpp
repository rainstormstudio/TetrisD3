/**
 * @file texture.hpp
 * @author Daniel Hongyu Ding
 * @brief This file defines the class for txt texture
 * @version 0.5
 * @date 2020-08-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#ifdef __linux__
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#elif _WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#endif

#include <vector>
#include <string>

struct CPixel {
    Uint8 ch;
    Uint8 r, g, b, a;
    Uint8 br, bg, bb, ba;

    bool operator==(const CPixel& other) {
        return ch == other.ch 
                && r == other.r 
                && g == other.g
                && b == other.b
                && a == other.a
                && br == other.br
                && bg == other.bg
                && bb == other.bb
                && ba == other.ba;
    }
};

class Texture {
    std::string filename;
    unsigned int numRows;
    unsigned int numCols;
    std::vector<std::vector<CPixel>> cpixels;
public:
    /**
     * @brief Construct a new Texture object
     * 
     * @param filename the txt texture file to be imported
     */
    Texture(std::string filename);

    /**
     * @brief import a txt texture file
     * 
     * @param filename the txt texture file to be imported
     */
    void importTxt(std::string filename);

    /**
     * @brief Get the Width of the texture
     * 
     * @return unsigned int 
     */
    unsigned int getWidth() const;

    /**
     * @brief Get the Height of the texture
     * 
     * @return unsigned int 
     */
    unsigned int getHeight() const;

    /**
     * @brief Get the Filename of the texture
     * 
     * @return std::string 
     */
    std::string getFilename() const;

    /**
     * @brief Get the texture information of the texture
     * at the y-th row and the x-th column
     * 
     * @param x the column number
     * @param y the row number
     * @return CPixel 
     */
    CPixel getInfo(int x, int y) const;
};

#endif
