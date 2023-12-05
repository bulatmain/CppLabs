#ifndef DECLARATIONS_H

#define DECLARATIONS_H

#include <memory>
#include <concepts>
#include <type_traits>
#include "declarations/container_traits.hpp"

namespace lab7 {
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
        ALIVE,
        DEAD,
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

    std::string statusToStr(statusOfNPC status) {
        switch (status)
        {
        case ALIVE:
            return "ALIVE";
        case DEAD:
            return "DEAD";
        default:
            return "UNKNOWN";
        }
    }

// Visitor's
    class Visitor;
    class AttackVisitor;
    template <template<typename> class T>
        requires Container<T<NPC*>>
    class SetNPCsInAttackRangeVisitor;

// Observers'
    class Observer;
    template <typename MessageBroker>
    class EventWriterObserver;
    template <typename MessageBroker>
    class KillEventObserver;

// Message brokers
    class ConsoleMessageBroker;
    class FileMessageBroker;
    
// Creators
    template<class T, class U>
    concept Derived = std::is_base_of<U, T>::value;

    class CreatorOfNPC;
    template <template <class> class Allocator>
    class CreatorOfOgre;
    template <template <class> class Allocator>
    class CreatorOfBear;
    template <template <class> class Allocator>
    class CreatorOfSquirrel;

// Auxiliary
    template <typename T>
    concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <Number T>
    struct point;
}

#endif