#ifndef DECLARATIONS_H

#define DECLARATIONS_H

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
    class CreatorOfNPC;
    class CreatorOfAttackNPC;
    class CreatorOfOgre;
    class CreatorOfBear;
    class CreatorOfSquirrel;

}

#endif