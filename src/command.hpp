#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "./EC_Core/entity.hpp"

class Command {
protected:
    Entity* entity;
public:
    Command(Entity* entity) : entity{entity} {}
    virtual void execute() = 0;
};

#endif
