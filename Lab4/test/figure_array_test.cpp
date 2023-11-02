#include "gtest/gtest.h"
#include "figure_array/figure_array.hpp"
#include "figure/rectangle.hpp"
#include "figure/rhombus.hpp"
#include "figure/trapeze.hpp"

using namespace lab4;

TEST(ConstructorGroup, Default) {
    FigureArray<int> a;

    EXPECT_TRUE(a.size() == 0);
}

TEST(ConstructorGroup, FromSize) {
    FigureArray<int> a(5);

    EXPECT_TRUE(a.size() == 5);
}

template <Number T>
struct figures_example_1 {
    std::shared_ptr<Rectangle<T>> rec = 
        std::shared_ptr<Rectangle<T>>(new Rectangle<T>({
            {0, 0},
            {1, 0},
            {1, 1},
            {0, 1}
        }));
    std::shared_ptr<Rhombus<T>> rh =
        std::shared_ptr<Rhombus<T>>(new Rhombus<T>({
            {0, 0},
            {2, 1},
            {3, 3},
            {1, 2}
        }));
    std::shared_ptr<Trapeze<T>> tr =
        std::shared_ptr<Trapeze<T>>(new Trapeze<T>({
            {0, 0},
            {4, 0},
            {3, 2},
            {1, 2}
        }));
};

template <Number T>
void checkForExample1(FigureArray<T>* a, figures_example_1<T>* fe) {
    EXPECT_TRUE(a->size() == 3);

    EXPECT_TRUE(*(*a)[0] == *fe->rec);
    EXPECT_TRUE(*(*a)[1] == *fe->rh);
    EXPECT_TRUE(*(*a)[2] == *fe->tr);
}

TEST(ConstructorGroup, FromInitList) {
    figures_example_1<int> fe;

    FigureArray<int> a({ fe.rec, fe.rh, fe.tr });

    checkForExample1(&a, &fe);
}

TEST(ConstructorGroup, CopyConstr) {
    figures_example_1<int> fe;

    FigureArray<int> a({ fe.rec, fe.rh, fe.tr });

    FigureArray<int> b(a);

    checkForExample1(&b, &fe);
}

TEST(ConstructorGroup, MoveConstr) {
    figures_example_1<int> fe;

    FigureArray<int> a({ fe.rec, fe.rh, fe.tr });

    FigureArray<int> b(std::move(a));

    checkForExample1(&b, &fe);

    EXPECT_TRUE(a.size() == 0);
}

TEST(CalcGroup, SummarySquare) {
    figures_example_1<double> fe;
    FigureArray<double> a({ fe.rec, fe.rh, fe.tr });

    ASSERT_EQ(a.summarySquare(), 10);
}

TEST(ElementsMovementGroup, EraseFigures1) {
    figures_example_1<double> fe;
    FigureArray<double> a({ fe.rec, fe.rh, fe.tr });

    a.eraseFigures(0, 1);
    ASSERT_EQ(a.summarySquare(), 9);
}

TEST(ElementsMovementGroup, EraseFigures2) {
    figures_example_1<double> fe;
    FigureArray<double> a({ fe.rec, fe.rh, fe.tr });

    a.eraseFigures(1, 2);
    ASSERT_EQ(a.summarySquare(), 7);
}

TEST(ElementsMovementGroup, EraseFigures3) {
    figures_example_1<double> fe;
    FigureArray<double> a({ fe.rec, fe.rh, fe.tr });

    a.eraseFigures(2, 3);
    ASSERT_EQ(a.summarySquare(), 4);
}

TEST(ElementsMovementGroup, EraseFigures4) {
    figures_example_1<double> fe;
    FigureArray<double> a({ fe.rec, fe.rh, fe.tr });

    a.eraseFigures(0, 3);
    ASSERT_EQ(a.summarySquare(), 0);
}

TEST(ElementsMovementGroup, AddFigure) {
    FigureArray<double> a;
    figures_example_1<double> fe;

    a.addFigure(fe.rec, 0);
    EXPECT_EQ(a.summarySquare(), 1);
    a.addFigure(fe.rh, 0);
    EXPECT_EQ(a.summarySquare(), 4);
    a.addFigure(fe.tr, 0);
    EXPECT_EQ(a.summarySquare(), 10);
}


int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}