#ifndef OBSERVER_HPP

#define OBSERVER_HPP

#include "declarations/declarations.hpp"

namespace lab6 {
    class Observer {
    public:
        virtual void update(NPC const* subject) = 0;
    };
};

#endif