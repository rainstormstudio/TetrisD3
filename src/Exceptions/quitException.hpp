#ifndef QUITEXCEPTION_HPP
#define QUITEXCEPTION_HPP

#include "gameException.hpp"

class QuitException : public GameException {
public:
    std::string msg() const override {
        return "quit exception met";
    }
};

#endif
