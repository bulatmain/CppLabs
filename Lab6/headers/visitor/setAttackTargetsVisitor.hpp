#ifndef SETATTACKTARGETSVISOTOR_HPP

#define SETATTACKTARGETSVISOTOR_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    class SetAttackTargetsVisitor : public Visitor {
    public:
        SetAttackTargetsVisitor() = default;
        SetAttackTargetsVisitor(std::list<NPC*> npcs) : npcs(npcs) {}

        void addNPC(NPC* npc);
        void eraseNPC(NPC* npc);

	    virtual void visitOgre(Ogre* ogre) const;
	    virtual void visitBear(Bear* bear) const;
    
    protected:
        std::list<NPC*> npcs;

    	virtual void setAttackTargets(AttackerNPC* attacker) const;
    };
};

#include "npc/attackerNPC.hpp"

void lab6::SetAttackTargetsVisitor::addNPC(lab6::NPC* npc) {
    npcs.emplace_back(npc);
}

void lab6::SetAttackTargetsVisitor::eraseNPC(lab6::NPC* npc) {
    npcs.erase(std::find(npcs.begin(), npcs.end(), npc));
}

void lab6::SetAttackTargetsVisitor::setAttackTargets(lab6::AttackerNPC* attacker) const {
    std::list<NPC*> _potentialAttackTargets;
    for (auto& potentialTarget : attacker->potentialAttackTargets) {
        if (distance(attacker->pos, potentialTarget->pos) <= attacker->attackStrength) {
            _potentialAttackTargets.emplace_back(potentialTarget);
        }
    }
    attacker->potentialAttackTargets = std::move(_potentialAttackTargets);
}

#endif