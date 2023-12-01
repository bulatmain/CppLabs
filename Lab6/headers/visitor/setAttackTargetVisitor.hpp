#ifndef SET_ATTACK_TARGET_HPP
#define SET_ATTACK_TARGET_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    class SetAttackTargetVisitor : public Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre, NPC* target = nullptr);
	    virtual void visitBear(Bear* bear, NPC* target = nullptr);
        
	    virtual void visitOgre(Ogre* ogre);
	    virtual void visitBear(Bear* bear);
    
    protected:
	    virtual void setTarget(AttackerNPC* attacker, NPC* target);
    };
}

#include "npc/attackerNPC.hpp"

void lab6::SetAttackTargetVisitor::visitOgre(lab6::Ogre* ogre) {
    setTarget(ogre, nullptr);
}

void lab6::SetAttackTargetVisitor::visitBear(lab6::Bear* bear) {
    setTarget(bear, nullptr);
}

void lab6::SetAttackTargetVisitor::visitOgre(lab6::Ogre* ogre, lab6::NPC* target) {
    setTarget(ogre, target);
}

void lab6::SetAttackTargetVisitor::visitBear(lab6::Bear* bear, lab6::NPC* target) {
    setTarget(bear, target);
}

void lab6::SetAttackTargetVisitor::setTarget(lab6::AttackerNPC* attacker, lab6::NPC* target) {
    if (target != nullptr) {
        attacker->attackTarget = target;
    } else {
        auto& pot_targets = attacker->potentialAttackTargets;
        if (attacker->attackTarget == nullptr &&
               pot_targets.begin() != pot_targets.end()) {
            attacker->attackTarget = *(pot_targets.begin());
        }
    }
}

#endif