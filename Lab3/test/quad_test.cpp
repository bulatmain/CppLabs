#include <gtest/gtest.h>

#include <iostream>

#include "lib/quadrilateral.h"

TEST(CalculationGroup, SquareOfQuadOf_FVm1_m4_FV4_1_FV4_3_FVm4_3_Eq) {
    flat_vector
        a(-1, -4),
        b( 4,  1),
        c( 4,  3),
        d(-4,  3);

    Quadrilateral q{a, b, c, d}; 

    ASSERT_EQ(q.square(), 33.0);
}

TEST(CalculationGroup, GeometricCenterTest1) {
    flat_vector
        a(0, 0),
        b(8, 0),
        c(7, 7),
        d(4, 5);

    Quadrilateral q{a, b, c, d}; 

    try {
        flat_vector s = q.geometricCenter();

        EXPECT_TRUE(double_eq_zero(s.x - 4.85185185185));
        EXPECT_TRUE(double_eq_zero(s.y - 2.51851851852));
    } catch(...) {
        FAIL();
    }
}

TEST(ComparationGroup, RotatedFigureIsEq) {
    Quadrilateral  q{{5, 2}, {8, 5}, {8, 8}, {3, 6}};
    Quadrilateral _q{{2, -5}, {5, -8}, {8, -8}, {6, -3}};

    ASSERT_TRUE(q == _q);
}

TEST(ComparationGroup, RotatedAndMovedFigureIsEq) {
    Quadrilateral  q{{5, 2}, {8, 5}, {8, 8}, {3, 6}};
    Quadrilateral _q{{-5, 10-2}, {-8, 10-5}, {-8, 10-8}, {-3, 10-6}};


    ASSERT_TRUE(q == _q);
}


int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}