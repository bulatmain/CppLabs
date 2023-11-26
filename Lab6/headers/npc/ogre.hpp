#ifndef OGRE_HPP

#define OGRE_HPP

#include "npc/attackerNPC.hpp"
#include "visitor/visitor.hpp"

namespace lab6 {
    class Ogre : public AttackerNPC {
        virtual void accept(Visitor* v) {
            v->visitOgre(this);
        }
    };
};

#endif