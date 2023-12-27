#ifndef BEAR_HPP

#define BEAR_HPP

#include "npc/npc.hpp"
#include "visitor/visitor.hpp"

namespace lab7 {
    class Bear : public NPC {
    public:
        virtual void accept(visitor_ptr v) {
            v->visitBear(this);
        }

        virtual typesOfNPCs identify();

        ~Bear() {};

        int getMovementDistance();
        int getAttackDistance();

    public:
        int movementDistance = 5;
        int attackDistance = 10;

    };
};

lab7::typesOfNPCs lab7::Bear::identify() {
    return typesOfNPCs::type_Bear;
}

int lab7::Bear::getMovementDistance() {
    return movementDistance;
}

int lab7::Bear::getAttackDistance() {
    return attackDistance;
}


#endif