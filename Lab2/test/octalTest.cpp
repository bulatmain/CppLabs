#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include "lib/octal.h"

#include "OctalTestingClass.hpp"
#include "auxiliary.h"

#define isSizeOfNAndNotNullArray(o, n) { \
    ASSERT_EQ((o).getSize(), n);           \
    ASSERT_NE((o).getArray(), nullptr);  \
}

TEST(OUTPUT, OUTPUT_OCTAL) {
    Octal a{1, 2, 3, 4, 5};

    std::cout << a << std::endl;

    ASSERT_TRUE(true);
}

// TEST Constructor

TEST(OctalConstructors, DefaultConstructorMakesNumberZero) {
    const OctalTest o;

    isSizeOfNAndNotNullArray(o, 1);

    ASSERT_EQ(o.getArray()[0], OctalDigit('0'));

}

TEST(AuxilaryFunctions, sizeByNumer_12345OctalIntEq_5Int) {
    ASSERT_EQ(sizeByNumber(012345), 5);
}

TEST(OctalConstructors, OctalOf_12345OctalIntrEq_12345OC) {
    const OctalTest o(012345);

    isSizeOfNAndNotNullArray(o, 5);

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(o.getArray()[i], '5' - i);
    }
}

TEST(OctalConstructors, OctalOf_5IntAnd_5UCEq_55555OC) {
    const OctalTest o(5, '5');

    isSizeOfNAndNotNullArray(o, 5);

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(o.getArray()[i], '5');
    }
}

TEST(OctalConstructors, OctalOfInitList_12345UCEq_12345OC) {
    const OctalTest o{ '1', '2', '3', '4', '5' };

    isSizeOfNAndNotNullArray(o, 5);

    for (int i = 0; i < 5; ++i ) {
        ASSERT_EQ(o.getArray()[i], '5' - i);
    }
}

TEST(OctalConstructors, OctalOf_12345StrEq_12345OC) {
    const std::string str = "12345";
    const OctalTest o(str);

    isSizeOfNAndNotNullArray(o, 5);

    for (int i = 0; i < 5; ++i ) {
        ASSERT_EQ(o.getArray()[i], '5' - i);
    }
}


TEST(OctalConstructors, OctalOf_12345OctalEq_12345OC) {
    const OctalTest first(012345);
    isSizeOfNAndNotNullArray(first, 5);
    
    const OctalTest second(first);
    isSizeOfNAndNotNullArray(second, 5);

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(first.getArray()[i], second.getArray()[i]);
    }
}


TEST(OctalConstructors, OctalOf_54321MovedOCEq_54321OC) {
    OctalTest first(054321);
    isSizeOfNAndNotNullArray(first, 5);

    OctalTest second = std::move(first);
    isSizeOfNAndNotNullArray(second, 5);

    ASSERT_EQ(first.getSize(), 0);
    ASSERT_EQ(first.getArray(), nullptr);

    for (int i = 0; i < 5; ++i ) {
        ASSERT_EQ(second.getArray()[i], i + '1');
    }
}

// Test Assign

TEST(OctalAssign, OctalAssigned_12345OCEq_12345OC) {
    OctalTest a(012345), b;
    isSizeOfNAndNotNullArray(a, 5);
    isSizeOfNAndNotNullArray(b, 1);

    b = a;

    ASSERT_TRUE(a == b);
}

TEST(OctalAssign, OctalMoved_12345OCEq_12345OC) {
    OctalTest a(012345), b, c;
    isSizeOfNAndNotNullArray(a, 5);
    isSizeOfNAndNotNullArray(b, 1);
    isSizeOfNAndNotNullArray(c, 1);

    c = a;

    b = std::move(a);

    ASSERT_TRUE(b == c);

    ASSERT_TRUE((a.getSize() == 0) &&
                (a.getArray() == nullptr));
}

// TEST Arithmetic

TEST(OctalPlusAssign, _17OCPa_7770OCEq_1117OC) {
    OctalTest a(017), b(07770), ans(010007);

    a += b;

    ASSERT_TRUE(a == ans);
}

TEST(OctalPlusAssign, _777CPa_777OCEq_1776OC) {
    OctalTest a(0777), b(0777), ans(01776);

    a += b;

    ASSERT_TRUE(a == ans);
}

TEST(OctalPlusAssign, _111CPa_111OCEq_222OC) {
    OctalTest a(0111), b(0111), ans(0222);

    a += b;

    ASSERT_TRUE(a == ans);
}

TEST(OctalPlusAssign, _0CPa_42OCEq_42OC) {
    OctalTest a(0), b(042), ans(042);

    a += b;

    ASSERT_TRUE(a == ans);
}

TEST(OctalPlus, _17OCPa_7770OCEq_1117OC) {
    OctalTest a(017), b(07770), ans(010007);

    OctalTest c = a + b;

    ASSERT_TRUE(c == ans);
}

TEST(OctalPlus, _777CPa_777OCEq_1776OC) {
    OctalTest a(0777), b(0777), ans(01776);

    OctalTest c = a + b;

    ASSERT_TRUE(c == ans);
}

TEST(OctalPlus, _111CPa_111OCEq_222OC) {
    OctalTest a(0111), b(0111), ans(0222);

    OctalTest c = a + b;

    ASSERT_TRUE(c == ans);
}

TEST(OctalPlus, _0CPa_42OCEq_42OC) {
    OctalTest a(0), b(042), ans(042);

    OctalTest c = a + b;

    ASSERT_TRUE(c == ans);
}

TEST(OctalMinusAssign, _100001CPa_2OCEq_77777OC) {
    OctalTest a(0100001), b(02), ans(077777);

    a -= b;

    ASSERT_TRUE(a == ans);
}

TEST(OctalMinusAssign, _777CPa_222OCEq_555OC) {
    OctalTest a(0777), b(0222), ans(0555);

    a -= b;

    ASSERT_TRUE(a == ans);
}

TEST(OctalMinusAssign, _1CPa_10OCThrowExeption) {
    OctalTest a(01), b(010);

    try {
        a -= b;
        FAIL() << "No exeption throwed!\n";
    } catch (std::invalid_argument e) {
        ASSERT_TRUE(true);
    } catch (...) {
        FAIL() << "Different exeption throwed!\n";
    }
}

// TEST Comparation

TEST(OctalComparators, _12345OCIsEqTo_12345OC) {
    OctalTest a{ 1, 2, 3, 4, 5 };
    OctalTest b{ 1, 2, 3, 4, 5 };

    ASSERT_TRUE(a == b);
}

TEST(OctalComparators, _12345OCIsNeqTo_1234OC) {
    OctalTest a{ 1, 2, 3, 4, 5 };
    OctalTest b{ 1, 2, 3, 4 };

    ASSERT_FALSE(a == b);
}

TEST(OctalComparators, _12345OCIsNeqTo_12346OC) {
    OctalTest a{ 1, 2, 3, 4, 5};
    OctalTest b{ 1, 2, 3, 4, 6 };

    ASSERT_FALSE(a == b);
}

TEST(OctalComparators, _1234OCLess_12346OC) {
    OctalTest a{ 1, 2, 3, 4 };
    OctalTest b{ 1, 2, 3, 4, 6 };

    ASSERT_TRUE(a < b);
}

TEST(OctalComparators, _12345OCLess_12346OC) {
    OctalTest a{ 1, 2, 3, 4, 5 };
    OctalTest b{ 1, 2, 3, 4, 6 };

    ASSERT_TRUE(a < b);
}

TEST(OctalComparators, _12345CNotLess_1234OC) {
    OctalTest a{ 1, 2, 3, 4, 5 };
    OctalTest b{ 1, 2, 3, 4 };

    ASSERT_FALSE(a < b);
}

TEST(OctalComparators, _12345CNotLess_12345OC) {
    OctalTest a{ 1, 2, 3, 4, 5 };
    OctalTest b{ 1, 2, 3, 4, 5 };

    ASSERT_FALSE(a < b);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}