#ifndef BEAR_HPP

#define BEAR_HPP

#include "npc/attackerNPC.hpp"
#include "visitor/visitor.hpp"

namespace lab6 {
    class Bear : public AttackerNPC {
    public:
        virtual void accept(Visitor* v) {
            v->visitBear(this);
        }
    };
};

#endif