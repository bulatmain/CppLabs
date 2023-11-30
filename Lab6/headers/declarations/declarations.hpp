#ifndef DECLARATIONS_H

#define DECLARATIONS_H

#include <memory>
#include "declarations/container_traits.hpp"

namespace lab6 {
// NPC's
    class NPC;
    class AttackerNPC;
    class Ogre;
    class Bear;
    class Squirrel;

    enum typesOfNPCs {
        type_NPC,
        type_AttackerNPC,
        type_Ogre,
        type_Bear, 
        type_Squirrel
    };

    enum statusOfNPC {
        DEAD,
        ALIVE
    };

// Visitor's
    class Visitor;
    class AttackVisitor;
    template <template<typename> class T>
        requires Container<T<NPC*>>
    class SetAttackTargetsVisitor;

// Observers'
    class Observer;
    class StatePrinterObserver;
    class SerializationObserver;
    
// Creators
    template<class T, class U>
    concept Derived = std::is_base_of<U, T>::value;

    class CreatorOfNPC;
    template <class Allocator>
    class CreatorOfOgre;
    template <class Allocator>
    class CreatorOfBear;
    template <class Allocator>
    class CreatorOfSquirrel;

}

#endif