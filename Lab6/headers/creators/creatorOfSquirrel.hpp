#ifndef CREATOR_OF_SQUIRREL
#define CREATOR_OF_SQUIRREL

#include <concepts>
#include "creators/creatorOfNPC.hpp"

namespace lab6 { 
    template<class Allocator = std::allocator<lab6::Squirrel>>
    class CreatorOfSquirrel : public CreatorOfNPC {
    public:
        CreatorOfSquirrel() = default;
        virtual void createNPC();
        void initialize(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status
        );
        void construct(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status
        );
    protected:
        Allocator allocator;
    private:
        CreatorOfSquirrel(const CreatorOfSquirrel&);
        CreatorOfSquirrel& operator=(const CreatorOfSquirrel&);
    };  
};

#include "npc/squirrel.hpp"

template <class Allocator>
void lab6::CreatorOfSquirrel<Allocator>::createNPC() {
    using traits = std::allocator_traits<Allocator>;
    lab6::Squirrel* sq = traits::allocate(allocator, 1);
    traits::construct(allocator, sq);
    npc = sq;
}

template <class Allocator>
void lab6::CreatorOfSquirrel<Allocator>::initialize(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status
) {
    if (npc == nullptr) {
        throw std::logic_error("Error: trying initialize not existing object\n");
    }
    using traits = std::allocator_traits<Allocator>;
    lab6::Squirrel* squirrel = dynamic_cast<lab6::Squirrel*>(npc);
    traits::construct(allocator, &squirrel->name, name);
    traits::construct(allocator, &squirrel->pos, pos);
    traits::construct(allocator, &squirrel->status, status);
}

template <class Allocator>
void lab6::CreatorOfSquirrel<Allocator>::construct(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status
) {
    createNPC();
    initialize(
        name,
        pos,
        status
    );
}

#endif