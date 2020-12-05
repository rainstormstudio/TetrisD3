#include "collider.hpp"
#include "appearance.hpp"
#include "gamefield.hpp"
#include "../../EC_Core/entityManager.hpp"
#include "../../texture.hpp"
#include "../../debug.hpp"

void Collider::changeCollider(int x, int y, int w, int h) {
    Appearance* appearance = owner->getComponent<Appearance>();
    Texture* texture = appearance->getTexture();
    if (texture) {
        collider.resize(h);
        for (int i = 0; i < collider.size(); i ++) {
            collider[i].resize(w);
            for (int j = 0; j < collider[i].size(); j ++) {
                CPixel* info = texture->getInfo(j + x, i + y);
                CPixel* transparent = new CPixel();
                if (*info != *transparent) {
                    collider[i][j] = true;
                } else {
                    collider[i][j] = false;
                }
                delete transparent;
            }
        }
    }
}

bool Collider::willCollide(int rowIndex, int colIndex, int x, int y, int w, int h) {
    Appearance* appearance = owner->getComponent<Appearance>();
    Texture* texture = appearance->getTexture();
    if (texture) {
        std::vector<std::vector<bool>> temp;
        temp.resize(h);
        for (int i = 0; i < temp.size(); i ++) {
            temp[i].resize(w);
            for (int j = 0; j < temp[i].size(); j ++) {
                CPixel* info = texture->getInfo(j + x, i + y);
                CPixel* transparent = new CPixel();
                if (*info != *transparent) {
                    temp[i][j] = true;
                } else {
                    temp[i][j] = false;
                }
                delete transparent;
            }
        }
        for (int i = 0; i < h; i ++) {
            for (int j = 0; j < w; j ++) {
                if (temp[i][j]) {
                    int a = j + colIndex;
                    int b = i + rowIndex;
                    Entity* gamefield = owner->manager.getEntityByName("Playfield");
                    GameField* playfield = gamefield->getComponent<GameField>();
                    if (playfield->isOccupied(b, a)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}