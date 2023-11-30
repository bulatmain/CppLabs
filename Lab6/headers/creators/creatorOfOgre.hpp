#ifndef CREATOR_OF_OGRE
#define CREATOR_OF_OGRE

#include <concepts>
#include "creators/creatorOfNPC.hpp"

namespace lab6 { 
    template<class Allocator = std::allocator<lab6::Ogre>>
    class CreatorOfOgre : public CreatorOfNPC {
    public:
        CreatorOfOgre() = default;
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
        CreatorOfOgre(const CreatorOfOgre&);
        CreatorOfOgre& operator=(const CreatorOfOgre&);

        void readVariables(
            std::string& name,
            point<size_t>& pos,
            statusOfNPC& status,
            const std::string& filename
        );
    };  
};

#include "npc/ogre.hpp"

template <class Allocator>
void lab6::CreatorOfOgre<Allocator>::readFromFile(const std::string& filename) {
    std::string name;
    point<size_t> pos;
    statusOfNPC status;
    readVariables(name, pos, status, filename);
    construct(name, pos, status, nullptr);
}

template <class Allocator>
void lab6::CreatorOfOgre<Allocator>::readVariables(
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
void lab6::CreatorOfOgre<Allocator>::construct(
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
            statusOfNPC status,
            lab6::NPC* attackTarget 
) {
    if (npc == nullptr) {
        throw std::logic_error("Error: trying initialize not existing object\n");
    }
    using traits = std::allocator_traits<Allocator>;
    lab6::Ogre* ogre = static_cast<lab6::Ogre*>(npc);
    traits::construct(allocator, &ogre->name, name);
    traits::construct(allocator, &ogre->pos, pos);
    traits::construct(allocator, &ogre->status, status);
    traits::construct(allocator, &ogre->attackTarget, attackTarget);
}



#endif