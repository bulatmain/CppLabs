#include <gtest/gtest.h>
#include "../exec/gameModel.hpp"

using namespace lab7;

TEST(Creators, CreateFromArguments) {
    CreatorOfBear creatorOfBear;
    creatorOfBear.construct("La Bear!", {1, 2}, ALIVE);

    npc_ptr bear = creatorOfBear.getNPC();

    ASSERT_TRUE(bear->name == "La Bear!");
    ASSERT_TRUE(bear->pos.x == 1 && bear->pos.y == 2);
    ASSERT_TRUE(bear->status == ALIVE);
}

TEST(AuxiliryFunctions, isInRange1) {
    CreatorOfBear cob;
    cob.construct("Bear", {0, 0}, ALIVE);
    npc_ptr bear = cob.getNPC();

    CreatorOfSquirrel cos;
    cos.construct("Squirrel", {0, 5}, ALIVE);
    npc_ptr squirrel = cos.getNPC();

    ASSERT_TRUE(isInRange(bear, squirrel));
}

TEST(AuxiliryFunctions, isInRange2) {
    CreatorOfBear cob;
    cob.construct("Bear", {0, 0}, ALIVE);
    npc_ptr bear = cob.getNPC();

    CreatorOfSquirrel cos;
    cos.construct("Squirrel", {0, 11}, ALIVE);
    npc_ptr squirrel = cos.getNPC();

    ASSERT_FALSE(isInRange(bear, squirrel));
}

TEST(AuxiliryFunctions, WillNotOverflow1_true) {
    size_t a = SIZE_MAX - 1;
    int b = 1;

    ASSERT_TRUE(willNotOverflow(a, b));
}

TEST(AuxiliryFunctions, WillNotOverflow2_false) {
    size_t a = SIZE_MAX - 1;
    int b = 2;

    ASSERT_FALSE(willNotOverflow(a, b));
}

TEST(AuxiliryFunctions, WillNotOverflow3_false) {
    size_t a = 10;
    int b = -11;

    ASSERT_FALSE(willNotOverflow(a, b));
}

TEST(AuxiliryFunctions, newX1) {
    size_t edge_x = 100;
    size_t old_x = 90;
    int dx = 5;

    ASSERT_EQ(newX(old_x, dx, edge_x), old_x + dx);
}

TEST(AuxiliryFunctions, newX2) {
    size_t edge_x = 100;
    size_t old_x = 90;
    int dx = 11;

    ASSERT_EQ(newX(old_x, dx, edge_x), old_x);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return ::RUN_ALL_TESTS();
}