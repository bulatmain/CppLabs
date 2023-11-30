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

        virtual typesOfNPCs identify();
    };
};

lab6::typesOfNPCs lab6::Bear::identify() {
    return typesOfNPCs::type_Bear;
}

#endif