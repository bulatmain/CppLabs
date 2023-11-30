#ifndef SQUIRREL_HPP

#define SQUIRREL_HPP

#include "npc/attackerNPC.hpp"
#include "visitor/visitor.hpp"

namespace lab6 {
    class Squirrel : public NPC {
    public:
        virtual void accept(Visitor* v) {
            v->visitSquirrel(this);
        }

        virtual typesOfNPCs identify();
    };
};

lab6::typesOfNPCs lab6::Squirrel::identify() {
    return typesOfNPCs::type_Squirrel;
}

#endif