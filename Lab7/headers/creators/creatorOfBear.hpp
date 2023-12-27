#ifndef CREATOR_OF_BEAR
#define CREATOR_OF_BEAR

#include <concepts>
#include "creators/creatorOfNPC.hpp"

namespace lab7 { 
    template<template <class> class Allocator = std::allocator>
    class CreatorOfBear : public CreatorOfNPC {
    public:
        using super = CreatorOfNPC;

        CreatorOfBear() = default;
        virtual void createNPC();
        void readFromFile(const std::string& filename);
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
        Allocator<Bear> allocator;

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

template <template <class> class Allocator>
void lab7::CreatorOfBear<Allocator>::readFromFile(const std::string& filename) {
    std::string name;
    point<size_t> pos;
    statusOfNPC status;
    readVariables(name, pos, status, filename);
    construct(name, pos, status);
}

template <template <class> class Allocator>
void lab7::CreatorOfBear<Allocator>::readVariables(
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
void lab7::CreatorOfBear<Allocator>::construct(
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

template <template <class> class Allocator>
void lab7::CreatorOfBear<Allocator>::createNPC() {
    using traits = std::allocator_traits<Allocator<Bear>>;
    lab7::Bear* bear = traits::allocate(allocator, 1);
    traits::construct(allocator, bear);
    npc = std::shared_ptr<NPC>(bear);
}

template <template <class> class Allocator>
void lab7::CreatorOfBear<Allocator>::initialize(
            const std::string& name,
    	    point<size_t> pos,
            statusOfNPC status
) {
    if (npc == nullptr) {
        throw std::logic_error("Error: trying initialize not existing object\n");
    }
    using traits = std::allocator_traits<Allocator<Bear>>;
    lab7::Bear* bear = dynamic_cast<lab7::Bear*>(npc.get());
    traits::construct(allocator, &bear->name, name);
    traits::construct(allocator, &bear->pos, pos);
    traits::construct(allocator, &bear->status, status);
}


#endif