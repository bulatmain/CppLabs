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
	    virtual void recieveDamage(NPC* reciever, double damage) const;
    };
}

#include "npc/ogre.hpp"
#include "npc/bear.hpp"

void lab6::AttackVisitor::visitOgre(Ogre* ogre) const {
    attack(ogre, ogre->attackTarget);
    // ogre->notifyObservers();
    // ogre->attackTarget->notifyObservers();
}

void lab6::AttackVisitor::visitBear(Bear* bear) const {
    attack(bear, bear->attackTarget);
    bear->notifyObservers();
    bear->attackTarget->notifyObservers();
}

void lab6::AttackVisitor::visitSquirrel(Squirrel* squirrel) const {}

void lab6::AttackVisitor::attack(lab6::AttackerNPC* attacker, lab6::NPC* reciever) const {
    recieveDamage(reciever, attacker->attackStrength);
}

void lab6::AttackVisitor::recieveDamage(lab6::NPC* reciever, double damage) const {
    reciever->health -= damage;
}
    

#endif