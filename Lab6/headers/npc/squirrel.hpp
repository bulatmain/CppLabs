#ifndef Squirrel_HPP

#define Squirrel_HPP

#include "npc/attackerNPC.hpp"
#include "visitor/visitor.hpp"

namespace lab6 {
    class Squirrel : public NPC {
        virtual void accept(Visitor* v) {
            v->visitSquirrel(this);
        }
    };
};

#endif