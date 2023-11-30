#ifndef SETATTACKTARGETSVISOTOR_HPP

#define SETATTACKTARGETSVISOTOR_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    class SetAttackTargetsVisitor : public Visitor {
    public:
        using list_ptr = std::shared_ptr<const std::list<NPC*>>;
        SetAttackTargetsVisitor(list_ptr npcs, double attackDistance)
         : npcs(npcs), attackDistance(attackDistance) {}

	    virtual void visitOgre(Ogre* ogre) const;
	    virtual void visitBear(Bear* bear) const;
    
    protected:
        list_ptr npcs;

    	virtual void setAttackTargets(AttackerNPC* attacker) const;

        double attackDistance;
    };
};

#include "npc/attackerNPC.hpp"

void lab6::SetAttackTargetsVisitor::setAttackTargets(lab6::AttackerNPC* attacker) const {
    attacker->potentialAttackTargets.clear();
    for (auto const& potentialTarget : *npcs) {
        if (distance(attacker->pos, potentialTarget->pos) <= attackDistance) {
           attacker->potentialAttackTargets.emplace_back(potentialTarget);
        }
    }
}

#endif