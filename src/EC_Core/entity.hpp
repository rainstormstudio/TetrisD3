#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../types.hpp"
#include <typeinfo>

class Component;
class EntityManager;
class Game;

class Entity {
    bool isActive;
    std::map<const std::type_info*, Component*> componentTypes;
public:
    Game* game;
    EntityManager& manager;

    std::vector<Component*> components;
    std::string name;
    Layer::Type layer;

    Entity(Game* game, EntityManager& manager);
    Entity(Game* game, EntityManager& manager, std::string name, Layer::Type layer);

    ~Entity();

    void update();
    void render();

    bool isAlive() const;
    void destroy();

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... args) {
        T* component = new T(std::forward<TArgs>(args)...);
        component->owner = this;
        components.emplace_back(component);
        componentTypes[&typeid(*component)] = component;
        component->init();
        return *component;
    }

    template <typename T>
    bool hasComponent() const {
        return static_cast<bool>(componentTypes.count(&typeid(T)));
    }

    template <typename T>
    T* getComponent() {
        return static_cast<T*>(componentTypes[&typeid(T)]);
    }
};

#endif
