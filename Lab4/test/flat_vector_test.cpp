#include <gtest/gtest.h>

#include "flat_vector/flat_vector.hpp"


TEST(AlgebraOperatorsGroup, FV5_3__PlusEqFV1_2__EqFV6_5__) {
    flat_vector<double> a(5, 3), b(1, 2);

    a += b;

    ASSERT_TRUE((a.x == 6) && (a.y == 5));
}

TEST(AlgebraOperatorsGroup, FV10_6__MinusEqFV4_7__EqFV6_m1__) {
    flat_vector<double> a(10, 6), b(4, 7);

    a -= b;

    ASSERT_TRUE((a.x == 6) && (a.y == -1));
}

TEST(AlgebraOperatorsGroup, TildaFV9_m8__EqFVm9_8__) {
    flat_vector<double> a(9, -8);

    flat_vector<double> b = ~a;

    ASSERT_TRUE((b.x == -9) && (b.y == 8));
}

TEST(AlgebraOperatorsGroup, FV10_6__MultEq2__EqFV20_12__) {
    flat_vector<double> a(10, 6); int lambda = 2;

    a *= lambda;

    ASSERT_TRUE((a.x == 20) && (a.y == 12));
}

TEST(AlgebraOperatorsGroup, ScalarFV1_2__FV3_4__Eq11__) {
    flat_vector<double> a(1, 2), b(3, 4);

    int dot = a.dot(b);

    ASSERT_TRUE(dot == 11);
}

TEST(ComparationOperatorsGroup, FV3_4__EqFV3_4__) {
    flat_vector<double> a(3, 4), b(3, 4);

    bool result = a == b;

    ASSERT_TRUE(result);
}


TEST(CalcNonMemverFuncsGroup, IntersectionConstant) {
    flat_vector<double> 
            a(4, 1),
            b(2, 5),
            c(2, 2),
            d(5, 2);

    try {
        flat_vector<double> t = intersection(a, b, c, d);
        EXPECT_TRUE(eq_zero(t.x - 3.5));
        EXPECT_TRUE(eq_zero(t.y - 2.0));
    } catch(...) {
        FAIL();
    }
}

TEST(CalcNonMemverFuncsGroup, IntersectionPoint1) {
    flat_vector<double> 
            a(6, 4),
            b(6, 4),
            c(3, 3),
            d(9, 5);

    try {
        flat_vector<double> t = intersection(a, b, c, d);
        EXPECT_TRUE(eq_zero(t.x - 6.0));
        EXPECT_TRUE(eq_zero(t.y - 4.0));
    } catch(...) {
        FAIL();
    }
}

TEST(CalcNonMemverFuncsGroup, IntersectionPoint2) {
    flat_vector<double> 
            a(4, 1),
            b(4, 4),
            c(4, 4),
            d(7, 5);

    try {
        flat_vector<double> t = intersection(a, b, c, d);
        EXPECT_TRUE(eq_zero(t.x - 4.0));
        EXPECT_TRUE(eq_zero(t.y - 4.0));
    } catch(...) {
        FAIL();
    }
}

TEST(CalcNonMemverFuncsGroup, IntersectionParallel) {
    flat_vector<double> 
            a(2, 2),
            b(3, 4),
            c(3, 1),
            d(4, 3);

    try {
        flat_vector<double> t = intersection(a, b, c, d);
        FAIL();
    } catch(std::logic_error e) {
        ASSERT_STREQ(e.what(), "Lines do not cross");
    } catch(...) {
        FAIL();
    }
}

int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}