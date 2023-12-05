#include <gtest/gtest.h>
#include "../exec/headersList.hpp"

using namespace lab6;

TEST(CreatorOfNPC, ReadNPC) {
    CreatorOfOgre creatorOfOgre;
    creatorOfOgre.readFromFile("ogre_file");
    NPC* ogre = creatorOfOgre.getNPC();

    ASSERT_TRUE(ogre->name == "La Ogre!");
    ASSERT_TRUE(ogre->pos.x == 1 && ogre->pos.y == 1);
    ASSERT_TRUE(ogre->status == ALIVE);
}

TEST(CreatorOfNPC, CreateFromArguments) {
    CreatorOfBear creatorOfBear;
    creatorOfBear.construct("La Bear!", {1, 2}, ALIVE, nullptr);

    NPC* bear = creatorOfBear.getNPC();


    ASSERT_TRUE(bear->name == "La Bear!");
    ASSERT_TRUE(bear->pos.x == 1 && bear->pos.y == 2);
    ASSERT_TRUE(bear->status == ALIVE);
}

TEST(Visitor, SetNPCsInAttackRangeVisitor) {
    CreatorOfOgre creatorOfOgre;
    creatorOfOgre.readFromFile("ogre_file");
    NPC* ogre = creatorOfOgre.getNPC();

    CreatorOfBear creatorOfBear;
    creatorOfBear.construct("La Bear!", {1, 2}, ALIVE, nullptr);

    NPC* bear = creatorOfBear.getNPC();

    CreatorOfSquirrel creatorOfSquirrel;
    creatorOfSquirrel.construct("La Squirrel!", {2, 1}, ALIVE);

    NPC* squirrel = creatorOfSquirrel.getNPC();

    std::list<NPC*> npcs = {ogre, bear, squirrel};

    SetNPCsInAttackRangeVisitor<std::list> setAttacKTargetsVisitor(&npcs, 10);

    for (auto npc : npcs) {
        npc->accept(&setAttacKTargetsVisitor);
    }

    AttackerNPC* aOgre = dynamic_cast<AttackerNPC*>(ogre);
    AttackerNPC* aBear = dynamic_cast<AttackerNPC*>(bear);

    ASSERT_TRUE(aOgre->potentialAttackTargets == std::list<NPC*>({bear, squirrel}));
    ASSERT_TRUE(aBear->potentialAttackTargets == std::list<NPC*>({ogre, squirrel}));

}

TEST(Visitor, SetAttackTrgetVisitor) {
    CreatorOfOgre creatorOfOgre;
    creatorOfOgre.readFromFile("ogre_file");
    NPC* ogre = creatorOfOgre.getNPC();

    CreatorOfBear creatorOfBear;
    creatorOfBear.construct("La Bear!", {1, 2}, ALIVE, nullptr);

    NPC* bear = creatorOfBear.getNPC();

    CreatorOfSquirrel creatorOfSquirrel;
    creatorOfSquirrel.construct("La Squirrel!", {2, 1}, ALIVE);

    NPC* squirrel = creatorOfSquirrel.getNPC();

    std::list<NPC*> npcs = {ogre, bear, squirrel};

    SetNPCsInAttackRangeVisitor<std::list> setAttacKTargetsVisitor(&npcs, 10);

    for (auto npc : npcs) {
        npc->accept(&setAttacKTargetsVisitor);
    }

    SetAttackTargetVisitor setAttackTargetVisitor;

    for (auto npc : npcs) {
        npc->accept(&setAttackTargetVisitor);
    }

    AttackerNPC* aOgre = dynamic_cast<AttackerNPC*>(ogre);
    AttackerNPC* aBear = dynamic_cast<AttackerNPC*>(bear);

    ASSERT_TRUE(aOgre->attackTarget == bear);
    ASSERT_TRUE(aBear->attackTarget == ogre);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return ::RUN_ALL_TESTS();
}