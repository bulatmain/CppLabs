#ifndef OGRE_HPP

#define OGRE_HPP

#include "npc/attackerNPC.hpp"
#include "visitor/visitor.hpp"

namespace lab7 {
    class Ogre : public AttackerNPC {
    public:
        virtual void accept(Visitor* v) {
            v->visitOgre(this);
        }

        virtual typesOfNPCs identify();

        ~Ogre() {};
    };
};


lab7::typesOfNPCs lab7::Ogre::identify() {
    return typesOfNPCs::type_Ogre;
}

#endif