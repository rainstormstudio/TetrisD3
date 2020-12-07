#include "tetromino.hpp"
#include "transform.hpp"
#include "appearance.hpp"
#include "collider.hpp"
#include "gamefield.hpp"
#include "soundeffects.hpp"
#include "../../debug.hpp"
#include "../../math.hpp"
#include "../../texture.hpp"
#include "../../media.hpp"

Tetromino::Tetromino() {
    direction = 0;
    type = TETRO_I;
    src = {0, 0, 0, 0};
    target = {0, 0, 0, 0};
    rowIndex = 19;
    colIndex = 4;
    hold = false;
}

Tetromino::~Tetromino() {
    Entity* gamefield = owner->manager.getEntityByName("Playfield");
    if (!gamefield) return;
    GameField* playfield = gamefield->getComponent<GameField>();

    Appearance* appearance = owner->getComponent<Appearance>();
    Texture* texture = appearance->getTexture();
    if (!texture) return;
    SDL_Rect src = appearance->getSrc();
    for (int x = 0; x < src.h; x ++) {
        for (int y = 0; y < src.w; y ++) {
            CPixel* info = texture->getInfo(y + src.x, x + src.y);
            playfield->occupy(rowIndex + x, colIndex + y, info);
        }
    }
}

void Tetromino::setHold(bool flag) {
    hold = flag;
}

void Tetromino::rotateRight() {
    if (!hold) return;
    Collider* collider = owner->getComponent<Collider>();
    int temp = (direction + 1) % 4;
    if (!collider->willCollide(rowIndex, colIndex, src.x + temp * src.w, src.y, src.w, src.h)) {
        direction = temp;
        Entity* gamefield = owner->manager.getEntityByName("Playfield");
        SoundEffects* sfx = gamefield->getComponent<SoundEffects>();
        sfx->triggerRotate();
    }
}

void Tetromino::rotateLeft() {
    if (!hold) return;
    Collider* collider = owner->getComponent<Collider>();
    int temp = (direction + 3) % 4;
    if (!collider->willCollide(rowIndex, colIndex, src.x + temp * src.w, src.y, src.w, src.h)) {
        direction = temp;
        Entity* gamefield = owner->manager.getEntityByName("Playfield");
        SoundEffects* sfx = gamefield->getComponent<SoundEffects>();
        sfx->triggerRotate();
    }
}

void Tetromino::moveRight() {
    if (!hold) return;
    Collider* collider = owner->getComponent<Collider>();
    if (!collider->willCollide(rowIndex, colIndex + 1, src.x + direction * src.w, src.y, src.w, src.h))
        colIndex ++;
}

void Tetromino::moveLeft() {
    if (!hold) return;
    Collider* collider = owner->getComponent<Collider>();
    if (!collider->willCollide(rowIndex, colIndex - 1, src.x + direction * src.w, src.y, src.w, src.h)) 
        colIndex --;
}

void Tetromino::moveDown() {
    if (!hold) return;
    Collider* collider = owner->getComponent<Collider>();
    if (!collider->willCollide(rowIndex + 1, colIndex, src.x + direction * src.w, src.y, src.w, src.h)) {
        rowIndex ++;
        Entity* gamefield = owner->manager.getEntityByName("Playfield");
        SoundEffects* sfx = gamefield->getComponent<SoundEffects>();
        sfx->triggerSoftDrop();
    } else {
        owner->destroy();
    }
}

void Tetromino::harddrop() {
    if (!hold) return;
    rowIndex = target.y;
    Entity* gamefield = owner->manager.getEntityByName("Playfield");
    SoundEffects* sfx = gamefield->getComponent<SoundEffects>();
    sfx->triggerHardDrop();
    GameField* playfield = gamefield->getComponent<GameField>();
    playfield->triggerAirflow(
        rowIndex + typeOffsets[type][direction * 3 + 1], 
        colIndex + typeOffsets[type][direction * 3 + 0], 
        typeOffsets[type][direction * 3 + 2]);
    owner->destroy();
}

void Tetromino::init() {
    static std::vector<TetroType> bag = {};
    if (bag.empty()) {
        bag = {TETRO_I, TETRO_J, TETRO_L, TETRO_S, TETRO_T, TETRO_Z};
        std::random_shuffle(bag.begin(), bag.end());
    }
    type = TetroType(bag.back());
    bag.pop_back();
    src = typeInfo[type];
}

void Tetromino::update() {
    if (hold) {
        Entity* playfield = owner->manager.getEntityByName("Playfield");
        Transform* playfieldTransform = playfield->getComponent<Transform>();

        Appearance* appearance = owner->getComponent<Appearance>();
        Transform* transform = owner->getComponent<Transform>();

        transform->position.x = playfieldTransform->position.x + 1 + colIndex;
        transform->position.y = playfieldTransform->position.y -19 + rowIndex;

        appearance->setSrc(src.x + direction * src.w, src.y, src.w, src.h);
        Collider* collider = owner->getComponent<Collider>();
        collider->changeCollider(src.x + direction * src.w, src.y, src.w, src.h);

        target = {colIndex, rowIndex, src.w, src.h};
        while (!collider->willCollide(target.y + 1, target.x, src.x + direction * src.w, src.y, src.w, src.h)) {
            target.y ++;
        }
    }
}

void Tetromino::render() {
    Media* gfx = owner->game->getGFX();
    Entity* interface = owner->manager.getEntityByName("Interface");
    Transform* interfaceTransform = interface->getComponent<Transform>();

    Appearance* appearance = owner->getComponent<Appearance>();
    Texture* texture = appearance->getTexture();
    if (hold) {
        Entity* playfield = owner->manager.getEntityByName("Playfield");
        Transform* playfieldTransform = playfield->getComponent<Transform>();

        SDL_Rect tsrc = {src.x + direction * src.w, src.y, src.w, src.h};
        SDL_Rect tdest = {static_cast<int>(round(interfaceTransform->position.x + 1)), 
                            static_cast<int>(round(interfaceTransform->position.y + 2)), 
                            src.w, src.h};
        if (src.w == 3) tdest.x ++;
        if (src.h == 3) tdest.y ++;
        gfx->drawTexture(texture, tsrc, tdest);
        tdest.x = target.x + playfieldTransform->position.x + 1;
        tdest.y = target.y + playfieldTransform->position.y -19;
        gfx->drawTexture(texture, tsrc, tdest, 0.3);
    } else {
        SDL_Rect tsrc = {src.x + direction * src.w, src.y, src.w, src.h};
        SDL_Rect tdest = {static_cast<int>(round(interfaceTransform->position.x + 17)), 
                            static_cast<int>(round(interfaceTransform->position.y + 1)), 
                            src.w, src.h};
        if (src.w == 3) tdest.x ++;
        if (src.h == 3) tdest.y ++;
        gfx->drawTexture(texture, tsrc, tdest);
    }
}




