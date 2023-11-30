#include <iostream>
#include "creators/creatorOfBear.hpp"
#include "creators/creatorOfSquirrel.hpp"
#include "npc/ogre.hpp"
#include "npc/squirrel.hpp"
#include "visitor/attackVisitor.hpp"
#include "visitor/setAttackTargetsVisitor.hpp"
#include "visitor/setAttackTargetVisitor.hpp"
#include "observer/killEventObserver.hpp"
#include "observer/messageBroker/fileMessageBroker.hpp"
#include "observer/messageBroker/consoleMessageBroker.hpp"
#include "auxiliry/point.hpp"
using namespace lab6;

int main() {

    FileMessageBroker fmb("killsStatus.txt");
    ConsoleMessageBroker cmb;

    KillEventObserver<FileMessageBroker> keo_file(std::move(fmb));
    KillEventObserver<ConsoleMessageBroker> keo_console(std::move(cmb));

    std::list<NPC*> npcs;

    SetAttackTargetsVisitor<std::list> setAttackTargetsVisitor(
        &npcs,
        10
    );
    SetAttackTargetVisitor setAttackTargetVisitor;
    AttackVisitor av;


    CreatorOfSquirrel cs;
    cs.readFromFile("squirrel_file");
    NPC* sq = cs.getNPC();

    CreatorOfBear cb;
    cb.readFromFile("bear_file");
    NPC* bear = cb.getNPC();

    npcs.emplace_back(sq);
    npcs.emplace_back(bear);

    for (auto& npc : npcs) {
        npc->attachObserver(&keo_file);
        npc->attachObserver(&keo_console);
    }

    for (auto& npc : npcs) {
        npc->accept(&setAttackTargetsVisitor);
    }

    for (auto& npc : npcs) {
        npc->accept(&setAttackTargetVisitor);
    }

    for (auto& npc : npcs) {
        npc->accept(&av);
    }
    
    return 0;
}