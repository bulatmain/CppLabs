#ifndef VISITOR_HPP

#define VISITOR_HPP

#include <string>

#include "declarations/declarations.h"
#include "auxiliry/point.hpp"

namespace lab6 {
    class Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre) const;
	    virtual void visitBear(Bear* bear) const;
	    virtual void visitSquirrel(Squirrel* squirrel) const; 

    protected:
        std::string& getNameOfNPC(NPC* npc) const;
        point<size_t>& getPosOfNPC(NPC* npc) const;
        double& getHealthOfNPC(NPC* npc) const;
    };
};

#include "npc/npc.hpp"

std::string& lab6::Visitor::getNameOfNPC(NPC* npc) const {
    return npc->name;
}

lab6::point<size_t>& lab6::Visitor::getPosOfNPC(NPC* npc) const {
    return npc->pos;
}

double& lab6::Visitor::getHealthOfNPC(NPC* npc) const {
    return npc->health;
}

#endif