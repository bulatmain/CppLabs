#ifndef DECLARATIONS_H

#define DECLARATIONS_H

#include <memory>
#include <concepts>
#include <type_traits>
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
        ALIVE,
        UNKNOWN
    };

    statusOfNPC strToStatus(std::string statusInString) {
        std::transform(statusInString.begin(), statusInString.end(), statusInString.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if (statusInString == "alive") {
            return ALIVE;
        } else if (statusInString == "dead"){
            return DEAD;
        } else {
            throw std::invalid_argument("Error: given string does not represent npc statusOfNPC.\n");
        }
    }

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

// Auxiliary
    template <typename T>
    concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <Number T>
    struct point;
}

#endif