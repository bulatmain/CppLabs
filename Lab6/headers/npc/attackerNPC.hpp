#ifndef ATTACKER_NPC_HPP

#define ATTACKER_NPC_HPP

#include "declarations/declarations.h"
#include "npc/npc.hpp"

namespace lab6 {
    class AttackerNPC : public NPC {
    protected:
	    double attackStrength;
	    std::list<NPC*> potentialAttackTargets;
	    NPC* attackTarget;

    public:
        virtual void accept(Visitor* v) = 0;

	    virtual double getAttackStrength() const;
        virtual std::list<NPC const*> getPotentialAttackTargets() const;
	    virtual NPC const* getAttackTarget() const;

        friend class AttackVisitor;
        friend class SetAttackTargetsVisitor;

    };
}

double lab6::AttackerNPC::getAttackStrength() const {
    return attackStrength;
}

std::list<lab6::NPC const*> lab6::AttackerNPC::getPotentialAttackTargets() const {
    std::list<lab6::NPC const*> _potentialAttackTargets;
    for (auto& target : potentialAttackTargets) {
        _potentialAttackTargets.emplace_back(target);
    }
    return _potentialAttackTargets;
}

lab6::NPC const* lab6::AttackerNPC::getAttackTarget() const {
    return attackTarget;
} 





#endif