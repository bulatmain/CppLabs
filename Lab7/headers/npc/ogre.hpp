#ifndef OGRE_HPP

#define OGRE_HPP

#include "npc/npc.hpp"
#include "visitor/visitor.hpp"

namespace lab7 {
    class Ogre : public NPC {
    public:
        virtual void accept(visitor_ptr v) {
            v->visitOgre(this);
        }

        virtual typesOfNPCs identify();

        ~Ogre() {};

        int getMovementDistance();
        int getAttackDistance();

    public:
        int movementDistance = 20;
        int attackDistance = 10;

    };
};

lab7::typesOfNPCs lab7::Ogre::identify() {
    return typesOfNPCs::type_Ogre;
}

int lab7::Ogre::getMovementDistance() {
    return movementDistance;
}

int lab7::Ogre::getAttackDistance() {
    return attackDistance;
}

#endif