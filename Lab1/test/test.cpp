#include <string>

#include <gtest/gtest.h>

#include <lib/header.hpp>

TEST(MainGroup, TwoBraketValid) {
    std::string input = "()";

    bool result = validateBraketString(input);

    ASSERT_EQ(result, true);
}

TEST(MainGroup, CloseBraketComesFirstInvalid) {
    std::string input = ")(()))";

    bool result = validateBraketString(input);

    ASSERT_EQ(result, false);
}

TEST(MainGroup, OneOpenBraketInvalid) {
    std::string input = "(";

    bool result = validateBraketString(input);

    ASSERT_EQ(result, false);
}

TEST(MainGroup, BigSequenceValid) {
    std::string input = "(())((()())())";

    bool result = validateBraketString(input);

    ASSERT_EQ(result, true);
}

TEST(MainGroup, EmptySequenceValid) {
    std::string input = "";

    bool result = validateBraketString(input);

    ASSERT_EQ(result, true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}