#ifndef GAMEEXCEPTION_HPP
#define GAMEEXCEPTION_HPP

#include <string>

class GameException {
public:
    virtual std::string msg() const = 0;
};

#endif
