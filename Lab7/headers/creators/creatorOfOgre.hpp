#ifndef CREATOR_OF_OGRE
#define CREATOR_OF_OGRE

#include <concepts>
#include "creators/creatorOfNPC.hpp"

namespace lab7 { 
    template<template <class> class Allocator = std::allocator>
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
        Allocator<Ogre> allocator;
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

template <template <class> class Allocator>
void lab7::CreatorOfOgre<Allocator>::readFromFile(const std::string& filename) {
    std::string name;
    point<size_t> pos;
    statusOfNPC status;
    readVariables(name, pos, status, filename);
    construct(name, pos, status, nullptr);
}

template <template <class> class Allocator>
void lab7::CreatorOfOgre<Allocator>::readVariables(
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

template <template <class> class Allocator>
void lab7::CreatorOfOgre<Allocator>::construct(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status,
            lab7::NPC* attackTarget 
) {
    createNPC();
    initialize(
        name,
        pos,
        status,
        attackTarget
    );
}

template <template <class> class Allocator>
void lab7::CreatorOfOgre<Allocator>::createNPC() {
    using traits = std::allocator_traits<Allocator<Ogre>>;
    lab7::Ogre* ogre = traits::allocate(allocator, 1);
    traits::construct(allocator, ogre);
    npc = ogre;
}

template <template <class> class Allocator>
void lab7::CreatorOfOgre<Allocator>::initialize(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status,
            lab7::NPC* attackTarget 
) {
    if (npc == nullptr) {
        throw std::logic_error("Error: trying initialize not existing object\n");
    }
    using traits = std::allocator_traits<Allocator<Ogre>>;
    lab7::Ogre* ogre = static_cast<lab7::Ogre*>(npc);
    traits::construct(allocator, &ogre->name, name);
    traits::construct(allocator, &ogre->pos, pos);
    traits::construct(allocator, &ogre->status, status);
    traits::construct(allocator, &ogre->attackTarget, attackTarget);
}



#endif