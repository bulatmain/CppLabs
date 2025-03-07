#ifndef SET_ATTACK_TARGETS_HPP

#define SET_ATTACK_TARGETS_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    template <template<typename> class T>
        requires Container<T<NPC*>>
    class SetNPCsInAttackRangeVisitor : public Visitor {
    public:
        using container_type = T<NPC*>;
        using container_ptr = T<NPC*> const*;
        SetNPCsInAttackRangeVisitor(container_ptr npcs, double attackDistance)
         : npcs(npcs), attackDistance(attackDistance) {}

	    virtual void visitOgre(Ogre* ogre);
	    virtual void visitBear(Bear* bear);

        virtual void setAttackDistance(double attackDistance) {
            this->attackDistance = attackDistance; 
        }
    
    protected:
        container_ptr npcs;
        double attackDistance;

    	virtual void setAttackTargets(AttackerNPC* attacker);

    };
};

#include "npc/attackerNPC.hpp"

template <template<typename> class T>
    requires lab6::Container<T<lab6::NPC*>>
void lab6::SetNPCsInAttackRangeVisitor<T>::visitOgre(Ogre* ogre) {
    setAttackTargets(ogre);
}

template <template<typename> class T>
    requires lab6::Container<T<lab6::NPC*>>
void lab6::SetNPCsInAttackRangeVisitor<T>::visitBear(Bear* bear) {
    setAttackTargets(bear);
}

template <template<typename> class T>
    requires lab6::Container<T<lab6::NPC*>>
void lab6::SetNPCsInAttackRangeVisitor<T>::setAttackTargets(lab6::AttackerNPC* attacker) {
    attacker->potentialAttackTargets.clear();
    for (auto const& potentialTarget : *npcs) {
        if (potentialTarget == attacker) {
            continue;
        } else if (distance(attacker->pos, potentialTarget->pos) <= attackDistance) {
           attacker->potentialAttackTargets.emplace_back(potentialTarget);
        }
    }
}

#endif