#include "entityManager.hpp"
#include "../debug.hpp"

EntityManager::EntityManager(Game* game)
    : game{game} {}

EntityManager::~EntityManager() {
    Debug::msg("delete manager");
    for (auto& entity : entities) {
        delete entity;
    }
}

void EntityManager::destroy() {
    for (unsigned int i = 0; i < entities.size(); ++i) {
        delete entities[i];
        entities.erase(entities.begin() + i);
        --i;
    }
}

void EntityManager::destroyByLayer(Layer::Type layer) {
    for (unsigned int i = 0; i < entities.size(); ++i) {
        if (entities[i]->layer == layer) {
            delete entities[i];
            entities.erase(entities.begin() + i);
            --i;
        }
    }
}

void EntityManager::update() {
    for (int layer = 0; layer < Layer::TOTAL; ++layer) {
        for (auto& entity : getEntitiesByLayer(static_cast<Layer::Type>(layer))) {
            entity->update();
        }
    }
    for (unsigned int i = 0; i < entities.size(); ++i) {
        if (!entities[i]->isAlive()) {
            delete entities[i];
            entities.erase(entities.begin() + i);
            --i;
        }
    }
}

void EntityManager::updateByLayer(Layer::Type layer) {
    for (auto& entity : getEntitiesByLayer(layer)) {
        entity->update();
    }
    for (unsigned int i = 0; i < entities.size(); ++i) {
        if (!entities[i]->isAlive()) {
            delete entities[i];
            entities.erase(entities.begin() + i);
            --i;
        }
    }
}

void EntityManager::render() {
    for (int layer = 0; layer < Layer::TOTAL; ++layer) {
        for (auto& entity : getEntitiesByLayer(static_cast<Layer::Type>(layer))) {
            entity->render();
        }
    }
}

Entity* EntityManager::addEntity(std::string name, Layer::Type layer) {
    Entity* entity = new Entity(game, *this, name, layer);
    entities.emplace_back(entity);
    return entity;
}

std::vector<Entity*> EntityManager::getEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::getEntitiesByLayer(Layer::Type layer) const {
    std::vector<Entity*> theEntities;
    for (auto& entity : entities) {
        if (entity->layer == layer) {
            theEntities.emplace_back(entity);
        }
    }
    return theEntities;
}

Entity* EntityManager::getEntityByName(std::string name) const {
    for (auto& entity : entities) {
        if (entity->name == name) {
            return entity;
        }
    }
    return nullptr;
}
