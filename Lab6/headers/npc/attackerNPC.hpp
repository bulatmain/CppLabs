#ifndef ATTACKER_NPC_HPP

#define ATTACKER_NPC_HPP

#include "npc/npc.hpp"

namespace lab6 {
    class AttackerNPC : public NPC {
    public:
	    std::list<NPC*> potentialAttackTargets;
	    NPC* attackTarget;

    public:
        virtual void accept(Visitor* v) = 0;

        virtual typesOfNPCs identify();
    };
}

lab6::typesOfNPCs lab6::AttackerNPC::identify() {
    return typesOfNPCs::type_AttackerNPC;
}

#endif