#include <string>

#include <gtest/gtest.h>

#include "lib/octalDigit.h"

TEST(OctalDigitConstructor, DefaultConstructorCShouldBe48) {
    OctalDigit d;

    ASSERT_EQ(d.c, '0');
}

TEST(OctalDigitConstructor, ConstructFromChar50ShouldBe50) {
    OctalDigit d('2');

    ASSERT_EQ(d.c, '2');
}

TEST(OctalDigitConstructor, ConstructFromChar42ShouldBeException) {
    try {
        OctalDigit d(42);
        FAIL() << "Expected std::invalid_argument\n";
    } catch (std::invalid_argument e) {
        ASSERT_TRUE(true);
    } catch (...) {
        FAIL() << "Expected std::invalid_argument\n";        
    }
}

TEST(OctalDigitConstructor, ConstructFromChar57ShouldBeException) {
    try {
        OctalDigit d('9');
        FAIL() << "Expected std::invalid_argument\n";
    } catch (std::invalid_argument e) {
        ASSERT_TRUE(true);
    } catch (...) {
        FAIL() << "Expected std::invalid_argument\n";        
    }
}

TEST(OctalDigitConstructor, ConstructFromOctalDigit7ShouldBe7) {
    OctalDigit a('7');

    OctalDigit b(a);

    ASSERT_TRUE(a.c == b.c);
}

TEST(OctalDigitAriphmeticOperator, OD50PlusEqUnsignedChar2ShouldBe52) {
    OctalDigit d('2');

    d += 2;

    ASSERT_EQ(d.c, '4');
}

TEST(OctalDigitAriphmeticOperator, OD54PlusEqUnsignedChar3ShouldBe1) {
    OctalDigit d('6');

    d += 3;

    ASSERT_EQ(d.c, '1');
}

TEST(OctalDigitAriphmeticOperator, OD52MinusEqUnsignedChar2ShouldBe50) {
    OctalDigit d('4');

    d -= 2;

    ASSERT_EQ(d.c, '2');
}

TEST(OctalDigitAriphmeticOperator, OD50PlusEqUnsignedChar3ShouldBe1) {
    OctalDigit d('2');

    d -= 3;

    ASSERT_EQ(d.c, '7');
}

TEST(OctalDigitCompareOperator, OD5EQOD5) {
    OctalDigit a('5'), b('5');

    ASSERT_TRUE(a == b);
}

TEST(OctalDigitCompareOperator, OD4LESSOD6) {
    OctalDigit a('4'), b('6');

    ASSERT_TRUE(a < b);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}