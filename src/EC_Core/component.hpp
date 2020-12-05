#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Entity;
class Game;

class Component {
public:
    Entity* owner;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    virtual ~Component() {}
};

#endif
