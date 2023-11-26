#ifndef ATTACKVISITOR_HPP

#define ATTACKVISITOR_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    class AttackVisitor : public Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre) const;
	    virtual void visitBear(Bear* bear) const;
	    virtual void visitSquirrel(Squirrel* squirrel) const; 
    
    protected:
    	virtual void attack(AttackerNPC* attacker, NPC* reciever) const;
	    virtual void setTarget(AttackerNPC* attacker) const;
	    virtual void recieveDamage(NPC* reciever, double damage) const;

        double& getAttackStrengthOfAttackerNPC(AttackerNPC* anpc) const;
        std::list<NPC*>& getPotentialAttackTargetsOfAttackerNPC(AttackerNPC* anpc) const;
        NPC*& getAttachTargetOfAttackerNPC(AttackerNPC* anpc) const;
    };
}

#include "npc/attackerNPC.hpp"

void lab6::AttackVisitor::attack(lab6::AttackerNPC* attacker, lab6::NPC* reciever) const {
    recieveDamage(reciever, attacker->attackStrength);
}

void lab6::AttackVisitor::setTarget(lab6::AttackerNPC* attacker) const {
    if (attacker->attackTarget == nullptr) {
        attacker->attackTarget = *attacker->potentialAttackTargets.begin();
    }
}

void lab6::AttackVisitor::recieveDamage(lab6::NPC* reciever, double damage) const {
    Visitor::getHealthOfNPC(reciever) -= damage;
}

double& lab6::AttackVisitor::getAttackStrengthOfAttackerNPC(lab6::AttackerNPC* anpc) const {
    return anpc->attackStrength;
}

std::list<lab6::NPC*>& lab6::AttackVisitor::getPotentialAttackTargetsOfAttackerNPC(lab6::AttackerNPC* anpc) const {
    return anpc->potentialAttackTargets;
}
        
lab6::NPC*& lab6::AttackVisitor::getAttachTargetOfAttackerNPC(lab6::AttackerNPC* anpc) const {
    return anpc->attackTarget;
}
    

#endif