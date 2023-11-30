#ifndef ATTACKER_NPC_HPP

#define ATTACKER_NPC_HPP

#include "declarations/declarations.h"
#include "npc/npc.hpp"

namespace lab6 {
    class AttackerNPC : public NPC {
    public:
	    double attackStrength;
	    std::list<NPC*> potentialAttackTargets;
	    NPC* attackTarget;

    public:
        virtual void accept(Visitor* v) = 0;
    };
}

#endif