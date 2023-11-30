#include <iostream>
#include "creators/creatorOfBear.hpp"
#include "creators/creatorOfSquirrel.hpp"
#include "npc/ogre.hpp"
#include "npc/squirrel.hpp"
#include "visitor/attackVisitor.hpp"
#include "auxiliry/point.hpp"
using namespace lab6;

int main() {
    CreatorOfSquirrel cs;
    cs.construct("Sq", {1, 2}, 100);
    NPC* sq = cs.getNPC();


    CreatorOfBear cb;
    cb.construct("Bear", {2, 2}, 100, 50, sq);
    NPC* bear = cb.getNPC();

    AttackVisitor av;

    bear->accept(&av);

    std::cout << sq->health << "\n";

    
    return 0;
}