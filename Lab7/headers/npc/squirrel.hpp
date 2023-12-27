#ifndef SQUIRREL_HPP

#define SQUIRREL_HPP

#include "npc/npc.hpp"
#include "visitor/visitor.hpp"

namespace lab7 {
    class Squirrel : public NPC {
    public:
        virtual void accept(visitor_ptr v) {
            v->visitSquirrel(this);
        }

        virtual typesOfNPCs identify();

        ~Squirrel() {};

        int getMovementDistance();
        int getAttackDistance();

    public:
        int movementDistance = 5;
        int attackDistance = 5;

    };
};

lab7::typesOfNPCs lab7::Squirrel::identify() {
    return typesOfNPCs::type_Squirrel;
}

int lab7::Squirrel::getMovementDistance() {
    return movementDistance;
}

int lab7::Squirrel::getAttackDistance() {
    return attackDistance;
}

#endif