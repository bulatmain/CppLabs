#ifndef SQUIRREL_HPP

#define SQUIRREL_HPP

#include "npc/attackerNPC.hpp"
#include "visitor/visitor.hpp"

namespace lab7 {
    class Squirrel : public NPC {
    public:
        virtual void accept(Visitor* v) {
            v->visitSquirrel(this);
        }

        virtual typesOfNPCs identify();

        ~Squirrel() {};
    };
};

lab7::typesOfNPCs lab7::Squirrel::identify() {
    return typesOfNPCs::type_Squirrel;
}

#endif