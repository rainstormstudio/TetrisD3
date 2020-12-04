#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "../types.hpp"
#include "entity.hpp"
#include "component.hpp"
#include "../game.hpp"

class EntityManager {
    Game* game;
protected:
    std::vector<Entity*> entities;
public:
    EntityManager(Game* game);
    ~EntityManager();

    void destroy();
    void destroyByLayer(Layer::Type layer);

    void update();
    void updateByLayer(Layer::Type layer);
    void render();

    Entity* addEntity(std::string name, Layer::Type layer);

    std::vector<Entity*> getEntities() const;
    std::vector<Entity*> getEntitiesByLayer(Layer::Type layer) const;
    Entity* getEntityByName(std::string name) const;
};

#endif
