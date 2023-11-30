#ifndef SET_ATTACK_TARGET_HPP
#define SET_ATTACK_TARGET_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    class SetAttackTargetVisitor : public Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre, NPC* target = nullptr) const;
	    virtual void visitBear(Bear* bear, NPC* target = nullptr) const;
	    virtual void visitOgre(Ogre* ogre) const;
	    virtual void visitBear(Bear* bear) const;
    
    protected:
	    virtual void setTarget(AttackerNPC* attacker, NPC* target) const;
    };
}

#include "npc/attackerNPC.hpp"

void lab6::SetAttackTargetVisitor::visitOgre(lab6::Ogre* ogre) const {
    setTarget(ogre, nullptr);
}

void lab6::SetAttackTargetVisitor::visitBear(lab6::Bear* bear) const {
    setTarget(bear, nullptr);
}

void lab6::SetAttackTargetVisitor::visitOgre(lab6::Ogre* ogre, lab6::NPC* target) const {
    setTarget(ogre, target);
}

void lab6::SetAttackTargetVisitor::visitBear(lab6::Bear* bear, lab6::NPC* target) const {
    setTarget(bear, target);
}

void lab6::SetAttackTargetVisitor::setTarget(lab6::AttackerNPC* attacker, lab6::NPC* target) const {
    if (target != nullptr) {
        attacker->attackTarget = target;
    } else if (attacker->attackTarget == nullptr) {
        attacker->attackTarget = *(attacker->potentialAttackTargets.begin());
    }
}

#endif