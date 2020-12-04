#include "ctexture.hpp"

CTexture::CTexture(SDL_Texture* texture, unsigned int numSrcRows, unsigned int numSrcCols, 
    unsigned int tileWidth, unsigned int tileHeight, unsigned int width, unsigned int height)
    : texture{texture}, numSrcRows{numSrcRows}, numSrcCols{numSrcCols} {
    background = texture;

    srcRect = {0, 0, static_cast<int>(tileWidth), static_cast<int>(tileHeight)};
    destRect = {0, 0, static_cast<int>(width), static_cast<int>(height)};
    
    foreColor = {255, 255, 255, 255};
    backColor = {0, 0, 0, 255};
}

CTexture::~CTexture() {
}

void CTexture::setIndex(Uint8 index) {
    srcRect.x = (index % numSrcCols) * srcRect.w;
    srcRect.y = (index / numSrcCols) * srcRect.h;
}

void CTexture::setDestPosition(int x, int y) {
    destRect.x = x;
    destRect.y = y;
}

void CTexture::setSrcPosition(int x, int y) {
    srcRect.x = x;
    srcRect.y = y;
}

void CTexture::setForeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    foreColor = {red, green, blue, alpha};
}

void CTexture::setBackColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    backColor = {red, green, blue, alpha};
}

void CTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture, blending);
}

void CTexture::render(SDL_Renderer* renderer) {
    SDL_SetTextureColorMod(background, backColor.r, backColor.g, backColor.b);
    SDL_SetTextureAlphaMod(background, backColor.a);
    SDL_Rect backSrcRect = {static_cast<int>((219 % numSrcCols) * srcRect.w), static_cast<int>((219 / numSrcCols) * srcRect.h), srcRect.w, srcRect.h};
    SDL_RenderCopyEx(renderer, background, &backSrcRect, &destRect, 0.0, nullptr, SDL_FLIP_NONE);
    SDL_SetTextureColorMod(texture, foreColor.r, foreColor.g, foreColor.b);
    SDL_SetTextureAlphaMod(texture, foreColor.a);
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0.0, nullptr, SDL_FLIP_NONE);
}
