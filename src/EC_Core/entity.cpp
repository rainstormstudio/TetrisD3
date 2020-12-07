#include "entity.hpp"
#include "component.hpp"
#include "entityManager.hpp"
#include "../game.hpp"
#include "../debug.hpp"

Entity::Entity(Game* game, EntityManager& manager)
    : game{game}, manager{manager} {
    isActive = true;
}

Entity::~Entity() {
    Debug::msg("delete entity: " + name, 3);
    for (unsigned int i = 0; i < components.size(); i ++) {
        Debug::msg("components size: " + std::to_string(components.size()), 4);
        delete components[i];
        components[i] = nullptr;
        Debug::msg("components size: " + std::to_string(components.size()), 4);
        components.erase(components.begin() + i);
        Debug::msg("components size: " + std::to_string(components.size()), 4);
        Debug::line(4);
        i --;
    }
    Debug::msg("entity deleted", 3);
}

Entity::Entity(Game* game, EntityManager& manager, std::string name, Layer::Type layer)
    : game{game}, manager{manager}, name{name}, layer{layer} {
    isActive = true;
}

void Entity::update() {
    for (unsigned int i = 0; i < components.size(); ++i) {
        components[i]->update();
    }
}

void Entity::render() {
    for (unsigned int i = 0; i < components.size(); ++i) {
        components[i]->render();
    }
}

bool Entity::isAlive() const { return isActive; }

void Entity::destroy() {
    isActive = false;
}
