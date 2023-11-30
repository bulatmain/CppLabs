#ifndef CREATOR_OF_OGRE
#define CREATOR_OF_OGRE

#include <concepts>
#include "declarations/declarations.h"
#include "creators/creatorOfNPC.hpp"

namespace lab6 { 
    template<class Allocator = std::allocator<lab6::Ogre>>
    class CreatorOfOgre : public CreatorOfNPC {
    public:
        CreatorOfOgre() = default;
        virtual void createNPC();
        void initialize(
            const std::string& name,
    	    point<size_t> pos,
            NPC* attackTarget
        );
        void construct(
            const std::string& name,
    	    point<size_t> pos,
            NPC* attackTarget
        );
    protected:
        Allocator allocator;
    private:
        CreatorOfOgre(const CreatorOfOgre&);
        CreatorOfOgre& operator=(const CreatorOfOgre&);
    };  
};

#include "npc/ogre.hpp"

template <class Allocator>
void lab6::CreatorOfOgre<Allocator>::createNPC() {
    using traits = std::allocator_traits<Allocator>;
    lab6::Ogre* ogre = traits::allocate(allocator, 1);
    traits::construct(allocator, ogre);
    npc = ogre;
}

template <class Allocator>
void lab6::CreatorOfOgre<Allocator>::initialize(
            const std::string& name,
    	    point<size_t> pos,
            lab6::NPC* attackTarget 
) {
    if (npc == nullptr) {
        throw std::logic_error("Error: trying initialize not existing object\n");
    }
    using traits = std::allocator_traits<Allocator>;
    lab6::Ogre* ogre = static_cast<lab6::Ogre*>(npc);
    traits::construct(allocator, &ogre->name, name);
    traits::construct(allocator, &ogre->pos, pos);
    traits::construct(allocator, &ogre->attackTarget, attackTarget);
}

template <class Allocator>
void lab6::CreatorOfOgre<Allocator>::construct(
            const std::string& name,
    	    point<size_t> pos,
            lab6::NPC* attackTarget 
) {
    createNPC();
    initialize(
        name,
        pos,
        attackTarget
    );
}

#endif