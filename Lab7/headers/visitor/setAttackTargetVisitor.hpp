#ifndef SET_ATTACK_TARGET_HPP
#define SET_ATTACK_TARGET_HPP

#include "visitor/visitor.hpp"

namespace lab7 {
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

void lab7::SetAttackTargetVisitor::visitOgre(lab7::Ogre* ogre) {
    setTarget(ogre, nullptr);
}

void lab7::SetAttackTargetVisitor::visitBear(lab7::Bear* bear) {
    setTarget(bear, nullptr);
}

void lab7::SetAttackTargetVisitor::visitOgre(lab7::Ogre* ogre, lab7::NPC* target) {
    setTarget(ogre, target);
}

void lab7::SetAttackTargetVisitor::visitBear(lab7::Bear* bear, lab7::NPC* target) {
    setTarget(bear, target);
}

void lab7::SetAttackTargetVisitor::setTarget(lab7::AttackerNPC* attacker, lab7::NPC* target) {
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