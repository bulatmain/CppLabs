#ifndef BEAR_HPP

#define BEAR_HPP

#include "npc/attackerNPC.hpp"
#include "visitor/visitor.hpp"

namespace lab7 {
    class Bear : public AttackerNPC {
    public:
        virtual void accept(Visitor* v) {
            v->visitBear(this);
        }

        virtual typesOfNPCs identify();

        ~Bear() {};
    };
};

lab7::typesOfNPCs lab7::Bear::identify() {
    return typesOfNPCs::type_Bear;
}

#endif