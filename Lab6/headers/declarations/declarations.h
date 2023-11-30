#ifndef DECLARATIONS_H

#define DECLARATIONS_H

#include <memory>

namespace lab6 {
// NPC's
    class NPC;
    class AttackerNPC;
    class Ogre;
    class Bear;
    class Squirrel;

// Visitor's
    class Visitor;
    class AttackVisitor;
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