#include "graphics.hpp"

Graphics::Graphics(std::string title, std::string tilesetFilename, 
                   unsigned int numSrcRows, unsigned int numSrcCols,
                   Uint32 fullscreenFlag, std::string fontPath,
                   unsigned int screenWidth, unsigned int screenHeight, 
                   unsigned int numRows, unsigned int numCols) 
    : title{title}, fullscreen{fullscreenFlag}, 
    numSrcRows{numSrcRows}, numSrcCols{numSrcCols},
    screenWidth{screenWidth}, screenHeight{screenHeight}, 
    numRows{numRows}, numCols{numCols} {
    
    window = nullptr;
    renderer = nullptr;
    font = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
    } else {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        SDL_SetWindowFullscreen(window, fullscreen);
        SDL_RaiseWindow(window);
        if (window == nullptr) {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        } else {
            renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            if (TTF_Init() == -1) {
                std::cerr << "TTF initialization failed: " << TTF_GetError() << std::endl;
            } else {
                font = TTF_OpenFont(fontPath.c_str(), 24);
                if (font == nullptr) {
                    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
                }
            }
            if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                std::cerr << "Failed to load SDL_image: " << IMG_GetError() << std::endl;
            }
        }
    }

    tileset = nullptr;
    SDL_Surface* surface = IMG_Load(tilesetFilename.c_str());
    if (surface == nullptr) {
        std::cerr << "Error initializing SDL surface: " << IMG_GetError() << std::endl;
    } else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
        tileset = SDL_CreateTextureFromSurface(renderer, surface);
        if (tileset == nullptr) {
            std::cerr << "Error creating texture from " << tilesetFilename << ": " << SDL_GetError() << std::endl;
        } else {
            tileWidth = surface->w / numSrcCols;
            tileHeight = surface->h / numSrcRows;
        }
        SDL_FreeSurface(surface);
    }

    textDisplay = std::vector<std::vector<std::shared_ptr<CTexture>>>(numRows);
    for (int i = 0; i < numRows; ++i) {
        textDisplay[i] = std::vector<std::shared_ptr<CTexture>>(numCols);
        for (int j = 0; j < numCols; ++j) {
            textDisplay[i][j] = std::make_shared<CTexture>(tileset, numSrcRows, numSrcCols, tileWidth, tileHeight, screenWidth/numCols, screenHeight/numRows);
            textDisplay[i][j]->setDestPosition(j*(screenWidth/numCols), i*(screenHeight/numRows));
        }
    }
}

void Graphics::setCh(Uint8 index, int x, int y) {
    if (x < numCols && y < numRows) {
        textDisplay[y][x]->setIndex(index);
    }
}

void Graphics::setForeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y) {
    if (x < numCols && y < numRows) {
        textDisplay[y][x]->setForeColor(r, g, b, a);
    }
}

void Graphics::setBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y) {
    if (x < numCols && y < numRows) {
        textDisplay[y][x]->setBackColor(r, g, b, a);
    }
}

void Graphics::drawPoint(CPixel* cpixel, int x, int y) {
    setCh(cpixel->ch, x, y);
    setForeColor(cpixel->r, cpixel->g, cpixel->b, cpixel->a, x, y);
    setBackColor(cpixel->br, cpixel->bg, cpixel->bb, cpixel->ba, x, y);
}

void Graphics::drawPoint(Uint8 ch, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba, int x, int y) {
    setCh(ch, x, y);
    setForeColor(r, g, b, a, x, y);
    setBackColor(br, bg, bb, ba, x, y);
}

void Graphics::importTxt(std::string filename, bool transparent) {
    std::string line;
    std::ifstream infile {filename};
    if (infile.is_open()) {
        int row = 0;
        while (std::getline(infile, line)) {
            int len = line.length();
            if (row < numRows) {
                for (int i = 0; i < len && i < numCols; ++i) {
                    if (!transparent || (transparent && line[i] != ' ')) {                        
                        textDisplay[row][i]->setIndex(line[i]);
                        textDisplay[row][i]->setForeColor(255, 255, 255, 255);
                        textDisplay[row][i]->setBackColor(0, 0, 0, 255);      
                    }
                }
                ++row;
            }
            
        }
    } else {
        std::cerr << "Could not open file " << filename << std::endl;
    }
}

void Graphics::write(std::string content, int x, int y) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    for (int i = 0; i < len && x + i < numCols; ++i) {
        textDisplay[y][x + i]->setIndex(content[i]);
    }
}

void Graphics::write(std::string content, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    for (int i = 0; i < len && x + i < numCols; ++i) {
        textDisplay[y][x + i]->setIndex(content[i]);
        textDisplay[y][x + i]->setForeColor(r, g, b, a);
    }
}

void Graphics::write(std::string content, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    for (int i = 0; i < len && x + i < numCols; ++i) {
        textDisplay[y][x + i]->setIndex(content[i]);
        textDisplay[y][x + i]->setForeColor(r, g, b, a);
        textDisplay[y][x + i]->setBackColor(br, bg, bb, ba);
    }
}

void Graphics::writeln(std::string content, int x, int y, int width) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    int j = 0;
    for (int i = 0; i < len; ++i) {
        textDisplay[y][x + j]->setIndex(content[i]);
        ++j;
        if (j == numCols || j == width) {
            ++y;
            j = 0;
        }
        if (y == numRows) {
            break;
        }
    }
}

void Graphics::writeln(std::string content, int x, int y, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    int j = 0;
    for (int i = 0; i < len; ++i) {
        textDisplay[y][x + j]->setIndex(content[i]);
        textDisplay[y][x + j]->setForeColor(r, g, b, a);
        ++j;
        if (j == numCols || j == width) {
            ++y;
            j = 0;
        }
        if (y == numRows) {
            break;
        }
    }
}

void Graphics::writeln(std::string content, int x, int y, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    int j = 0;
    for (int i = 0; i < len; ++i) {
        textDisplay[y][x + j]->setIndex(content[i]);
        textDisplay[y][x + j]->setForeColor(r, g, b, a);
        textDisplay[y][x + j]->setBackColor(br, bg, bb, ba);
        ++j;
        if (j == numCols || j == width) {
            ++y;
            j = 0;
        }
        if (y == numRows) {
            break;
        }
    }
}

void Graphics::drawTexture(const Texture* texture, const SDL_Rect &src, const SDL_Rect &dest) {
    if (texture) {
        for (int i = src.x; i < src.x + src.w; i ++) {
            for (int j = src.y; j < src.y + src.h; j ++) {
                CPixel* info = texture->getInfo(i, j);
                CPixel* transparent = new CPixel();
                if (*info != *transparent) {
                    int x = i - src.x + dest.x;
                    int y = j - src.y + dest.y;
                    setCh(info->ch, x, y);
                    setForeColor(info->r, info->g, info->b, info->a, x, y);
                    setBackColor(info->br, info->bg, info->bb, info->ba, x, y);
                }
                delete transparent;
            }
        }
    }
}

void Graphics::drawTexture(const Texture* texture, const SDL_Rect &src, const SDL_Rect &dest, double ratio) {
    if (texture) {
        for (int i = src.x; i < src.x + src.w; i ++) {
            for (int j = src.y; j < src.y + src.h; j ++) {
                CPixel* info = texture->getInfo(i, j);
                CPixel* transparent = new CPixel();
                if (*info != *transparent) {
                    int x = i - src.x + dest.x;
                    int y = j - src.y + dest.y;
                    setCh(info->ch, x, y);
                    setForeColor(info->r, info->g, info->b, static_cast<Uint8>(info->a * ratio), x, y);
                    setBackColor(info->br, info->bg, info->bb, static_cast<Uint8>(info->ba * ratio), x, y);
                }
                delete transparent;
            }
        }
    }
}

Graphics::~Graphics() {
    if (tileset != nullptr) {
        SDL_DestroyTexture(tileset);
        tileset = nullptr;
        tileWidth = 0;
        tileHeight = 0;
    }
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Graphics::clear() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            textDisplay[i][j]->setIndex(' ');
            textDisplay[i][j]->setForeColor(255, 255, 255, 255);
            textDisplay[i][j]->setBackColor(0, 0, 0, 255);
        }
    }
    SDL_RenderClear(renderer);
}

void Graphics::render() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            textDisplay[i][j]->render(renderer);
        }
    }
    SDL_RenderPresent(renderer);
}

unsigned int Graphics::getScreenRows() const { return numRows; }

unsigned int Graphics::getScreenCols() const { return numCols; }

unsigned int Graphics::getPosCol(int x) const {
    return static_cast<unsigned int>(x) / (screenWidth/numCols);
}

unsigned int Graphics::getPosRow(int y) const {
    return static_cast<unsigned int>(y) / (screenHeight/numRows);
}
