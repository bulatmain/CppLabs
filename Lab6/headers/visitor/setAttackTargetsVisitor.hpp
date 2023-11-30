#ifndef SET_ATTACK_TARGETS_HPP

#define SET_ATTACK_TARGETS_HPP

#include "visitor/visitor.hpp"

namespace lab6 {
    template <template<typename> class T>
        requires Container<T<NPC*>>
    class SetAttackTargetsVisitor : public Visitor {
    public:
        using container_type = T<NPC*>;
        using container_ptr = T<NPC*> const*;
        SetAttackTargetsVisitor(container_ptr npcs, double attackDistance)
         : npcs(npcs), attackDistance(attackDistance) {}

	    virtual void visitOgre(Ogre* ogre) const;
	    virtual void visitBear(Bear* bear) const;
    
    protected:
        container_ptr npcs;
        double attackDistance;

    	virtual void setAttackTargets(AttackerNPC* attacker) const;

    };
};

#include "npc/attackerNPC.hpp"

template <template<typename> class T>
    requires lab6::Container<T<lab6::NPC*>>
void lab6::SetAttackTargetsVisitor<T>::visitOgre(Ogre* ogre) const {
    setAttackTargets(ogre);
}

template <template<typename> class T>
    requires lab6::Container<T<lab6::NPC*>>
void lab6::SetAttackTargetsVisitor<T>::visitBear(Bear* bear) const {
    setAttackTargets(bear);
}

template <template<typename> class T>
    requires lab6::Container<T<lab6::NPC*>>
void lab6::SetAttackTargetsVisitor<T>::setAttackTargets(lab6::AttackerNPC* attacker) const {
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