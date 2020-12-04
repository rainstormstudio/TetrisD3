/**
 * @file ctexture.hpp
 * @author Daniel Hongyu Ding
 * @brief This file defines the class for cell texture
 * @version 0.5
 * @date 2020-08-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CTEXTURE_HPP
#define CTEXTURE_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <iostream>

class CTexture {
    SDL_Texture* texture;
    SDL_Texture* background;
    unsigned int numSrcRows;
    unsigned int numSrcCols;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    SDL_Color foreColor;
    SDL_Color backColor;
    
public:
    /**
     * @brief Construct a new CTexture object
     * 
     * @param texture the texture created from tileset image
     * @param numSrcRows number of rows in the tileset
     * @param numSrcCols number of columns in the tileset
     * @param tileWidth the width of every tile in the tileset
     * @param tileHeight the height of every tile int the tileset
     * @param width the width of the texture to be rendered
     * @param height the height of the texture to be rendered
     */
    CTexture(SDL_Texture* texture, unsigned int numSrcRows, unsigned int numSrcCols, 
             unsigned int tileWidth, unsigned int tileHeight,
             unsigned int width, unsigned int height);

    /**
     * @brief Destroy the CTexture object
     * 
     */
    ~CTexture();

    /**
     * @brief Set the srcRect to the corresponding index
     * 
     * @param index the index of the tile in the tileset
     */
    void setIndex(Uint8 index);

    /**
     * @brief Set the coordinates of the srcRect
     * 
     * @param x x-coordinates
     * @param y y-coordinates
     */
    void setDestPosition(int x, int y);

    /**
     * @brief Set the coordinates of the destRect
     * 
     * @param x x-coordinates
     * @param y y-coordinates
     */
    void setSrcPosition(int x, int y);

    /**
     * @brief Set the Fore Color to be (red, green, blue, alpha)
     * 
     * @param red red for foreColor
     * @param green green for foreColor
     * @param blue blue for foreColor
     * @param alpha alpha for foreColor
     */
    void setForeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

    /**
     * @brief Set the Back Color to be (red, green, blue, alpha)
     * 
     * @param red red for backColor
     * @param green green for backColor
     * @param blue blue for backColor
     * @param alpha alpha for backColor
     */
    void setBackColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

    /**
     * @brief Set the SDL Blend Mode
     * 
     * @param blending SDL Blend Mode
     */
    void setBlendMode(SDL_BlendMode blending);

    /**
     * @brief renders the cell texture to the screen
     * 
     * @param renderer the renderer to be rendered on
     */
    void render(SDL_Renderer* renderer);
};

#endif
