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
    Debug::enabled = true;
    Debug::msg("delete entity's components");
    Debug::enabled = false;
    for (auto& component : components) {
        delete component;
    }
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
