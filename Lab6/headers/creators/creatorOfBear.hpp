#ifndef CREATOR_OF_BEAR
#define CREATOR_OF_BEAR

#include <concepts>
#include "creators/creatorOfNPC.hpp"

namespace lab6 { 
    template<class Allocator = std::allocator<lab6::Bear>>
    class CreatorOfBear : public CreatorOfNPC {
    public:
        CreatorOfBear() = default;
        virtual void createNPC();
        void readFromFile(const std::string& filename);
        void initialize(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status,
            NPC* attackTarget
        );
        void construct(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status,
            NPC* attackTarget
        );
    protected:
        Allocator allocator;

    private:
        CreatorOfBear(const CreatorOfBear&);
        CreatorOfBear& operator=(const CreatorOfBear&);

        void readVariables(
            std::string& name,
            point<size_t>& pos,
            statusOfNPC& status,
            const std::string& filename
        );
    };  
};

#include "npc/bear.hpp"

template <class Allocator>
void lab6::CreatorOfBear<Allocator>::readFromFile(const std::string& filename) {
    std::string name;
    point<size_t> pos;
    statusOfNPC status;
    readVariables(name, pos, status, filename);
    construct(name, pos, status, nullptr);
}

template <class Allocator>
void lab6::CreatorOfBear<Allocator>::readVariables(
            std::string& name,
            point<size_t>& pos,
            statusOfNPC& status,
            const std::string& filename
) {
    try {
        std::ifstream fin(filename);
        readName(name, fin);
        readPos(pos, fin);
        readStatus(status, fin);
    } catch(const std::ios_base::failure& e) {
        throw std::runtime_error("Error: can not open file " + filename + "\n");
    } catch(const std::runtime_error& e) {
        throw e;
    }
}

template <class Allocator>
void lab6::CreatorOfBear<Allocator>::construct(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status,
            lab6::NPC* attackTarget 
) {
    createNPC();
    initialize(
        name,
        pos,
        status,
        attackTarget
    );
}

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
            statusOfNPC status,
            lab6::NPC* attackTarget 
) {
    if (npc == nullptr) {
        throw std::logic_error("Error: trying initialize not existing object\n");
    }
    using traits = std::allocator_traits<Allocator>;
    lab6::Bear* bear = dynamic_cast<lab6::Bear*>(npc);
    traits::construct(allocator, &bear->name, name);
    traits::construct(allocator, &bear->pos, pos);
    traits::construct(allocator, &bear->status, status);
    traits::construct(allocator, &bear->attackTarget, attackTarget);
}


#endif