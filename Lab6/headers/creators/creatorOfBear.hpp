#ifndef CREATOR_OF_BEAR
#define CREATOR_OF_BEAR

#include <concepts>
#include "declarations/declarations.h"
#include "creators/creatorOfNPC.hpp"

namespace lab6 { 
    template<class Allocator = std::allocator<lab6::Bear>>
    class CreatorOfBear : public CreatorOfNPC {
    public:
        CreatorOfBear() = default;
        virtual void createNPC();
        void initialize(
            const std::string& name,
    	    point<size_t> pos,
    	    double health,
            double attackStrength,
            NPC* attackTarget
        );
        void construct(
            const std::string& name,
    	    point<size_t> pos,
    	    double health,
            double attackStrength,
            NPC* attackTarget
        );
    protected:
        Allocator allocator;
    private:
        CreatorOfBear(const CreatorOfBear&);
        CreatorOfBear& operator=(const CreatorOfBear&);
    };  
};

#include "npc/bear.hpp"

template <class Allocator>
void lab6::CreatorOfBear<Allocator>::createNPC() {
    using traits = std::allocator_traits<Allocator>;
    lab6::Bear* bear = traits::allocate(allocator, 1);
    traits::construct(allocator, bear);
    npc = bear;
}

template <class Allocator>
void lab6::CreatorOfBear<Allocator>::initialize(
            const std::string& name,
    	    point<size_t> pos,
    	    double health,
            double attackStrength,
            lab6::NPC* attackTarget 
) {
    if (npc == nullptr) {
        throw std::logic_error("Error: trying initialize not existing object\n");
    }
    using traits = std::allocator_traits<Allocator>;
    lab6::Bear* bear = dynamic_cast<lab6::Bear*>(npc);
    traits::construct(allocator, &bear->name, name);
    traits::construct(allocator, &bear->pos, pos);
    traits::construct(allocator, &bear->health, health);
    traits::construct(allocator, &bear->attackStrength, attackStrength);
    traits::construct(allocator, &bear->attackTarget, attackTarget);
}

template <class Allocator>
void lab6::CreatorOfBear<Allocator>::construct(
            const std::string& name,
    	    point<size_t> pos,
    	    double health,
            double attackStrength,
            lab6::NPC* attackTarget 
) {
    createNPC();
    initialize(
        name,
        pos,
        health,
        attackStrength,
        attackTarget
    );
}

#endif