#ifndef ATTACKVISITOR_HPP

#define ATTACKVISITOR_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    class AttackVisitor : public Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre) const;
	    virtual void visitBear(Bear* bear) const; 
    protected:
    	virtual void ogreAttack(Ogre* attacker, NPC* reciever) const;
    	virtual void bearAttack(Bear* attacker, NPC* reciever) const;
        virtual void killNPC(NPC* reciever) const;

    };
}

#include "npc/ogre.hpp"
#include "npc/bear.hpp"

void lab6::AttackVisitor::visitOgre(Ogre* ogre) const {
    ogreAttack(ogre, ogre->attackTarget);
    ogre->notifyObservers();
    ogre->attackTarget->notifyObservers();
}

void lab6::AttackVisitor::visitBear(Bear* bear) const {
    bearAttack(bear, bear->attackTarget);
    bear->notifyObservers();
    bear->attackTarget->notifyObservers();
}

void lab6::AttackVisitor::ogreAttack(lab6::Ogre* attacker, lab6::NPC* reciever) const {
    switch (reciever->identify())
    {
    case type_Ogre:
    case type_Bear:
        killNPC(reciever);
        break;
    default:
        break;
    }
}

void lab6::AttackVisitor::bearAttack(lab6::Bear* attacker, lab6::NPC* reciever) const {
    switch (reciever->identify())
    {
    case type_Squirrel:
        killNPC(reciever);
        break;
    default:
        break;
    }
}    

void lab6::AttackVisitor::killNPC(NPC* reciever) const {
    reciever->status = DEAD;
}

#endif