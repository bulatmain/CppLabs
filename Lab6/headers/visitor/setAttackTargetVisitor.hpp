#ifndef ATTACKVISITOR_HPP

#define ATTACKVISITOR_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    class SetAttackTargetVisitor : public Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre, NPC* target = nullptr) const;
	    virtual void visitBear(Bear* bear, NPC* target = nullptr) const;
    
    protected:
	    virtual void setTarget(AttackerNPC* attacker, NPC* target) const;
    };
}

#include "npc/attackerNPC.hpp"
void lab6::SetAttackTargetVisitor::setTarget(lab6::AttackerNPC* attacker, lab6::NPC* target) const {
    if (target != nullptr) {
        attacker->attackTarget = target;
    } else if (attacker->attackTarget == nullptr) {
        attacker->attackTarget = *(attacker->potentialAttackTargets.begin());
    }
}


#endif