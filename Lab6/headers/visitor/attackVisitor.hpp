#ifndef ATTACKVISITOR_HPP

#define ATTACKVISITOR_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    class AttackVisitor : public Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre);
	    virtual void visitBear(Bear* bear); 
    protected:
    	virtual void ogreAttack(Ogre* attacker, NPC* reciever);
    	virtual void bearAttack(Bear* attacker, NPC* reciever);
        virtual void killNPC(NPC* reciever);

    };
}

#include "npc/ogre.hpp"
#include "npc/bear.hpp"

void lab6::AttackVisitor::visitOgre(Ogre* ogre) {
    ogreAttack(ogre, ogre->attackTarget);
}

void lab6::AttackVisitor::visitBear(Bear* bear) {
    bearAttack(bear, bear->attackTarget);
}

void lab6::AttackVisitor::ogreAttack(lab6::Ogre* attacker, lab6::NPC* reciever) {
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

void lab6::AttackVisitor::bearAttack(lab6::Bear* attacker, lab6::NPC* reciever) {
    switch (reciever->identify())
    {
    case type_Squirrel:
        killNPC(reciever);
        break;
    default:
        break;
    }
}    

void lab6::AttackVisitor::killNPC(NPC* reciever) {
    reciever->status = DEAD;
    reciever->notifyObservers();
}

#endif