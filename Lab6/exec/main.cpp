#include <iostream>
#include "creators/creatorOfBear.hpp"
#include "creators/creatorOfSquirrel.hpp"
#include "npc/ogre.hpp"
#include "npc/squirrel.hpp"
#include "visitor/attackVisitor.hpp"
#include "visitor/setAttackTargetsVisitor.hpp"
#include "visitor/setAttackTargetVisitor.hpp"
#include "auxiliry/point.hpp"
using namespace lab6;

int main() {
    std::list<NPC*> npcs;

    CreatorOfSquirrel cs;
    cs.construct("Sq", {1, 2}, ALIVE);
    NPC* sq = cs.getNPC();


    CreatorOfBear cb;
    cb.construct("Bear", {2, 2}, ALIVE, nullptr);
    NPC* bear = cb.getNPC();

    npcs.emplace_back(sq);
    npcs.emplace_back(bear);

    SetAttackTargetsVisitor<std::list> setAttackTargetsVisitor(
        &npcs, 
        10
    );
    SetAttackTargetVisitor setAttackTargetVisitor;
    AttackVisitor av;

    for (auto& npc : npcs) {
        npc->accept(&setAttackTargetsVisitor);
    }

    for (auto& npc : npcs) {
        npc->accept(&setAttackTargetVisitor);
    }

    for (auto& npc : npcs) {
        npc->accept(&av);
    }

    std::cout << sq->status << "\n";
    
    return 0;
}