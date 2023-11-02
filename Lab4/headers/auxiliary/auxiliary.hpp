#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "figure/rectangle.hpp"
#include "figure/rhombus.hpp"
#include "figure/trapeze.hpp"
#include "figure_array/figure_array.hpp"

using namespace lab4;

template <Number T>
void add_figure(FigureArray<T>& figures) {
    int code = -1;

    std::cout << "Please, pick which figure you'd like to add:\n";

    std::cout << 
    "1. Rectangle.\n" << 
    "2. Rhombus.\n" << 
    "3. Trapeze.\n";

    std::cin >> code;

    std::shared_ptr<Quadrilateral<T>> rec;

    if (code == 1) {
        rec = std::make_shared<Rectangle<T>>();   
    } else if (code == 2) {
        rec = std::make_shared<Rhombus<T>>();
    } else if (code == 3) {
        rec = std::make_shared<Trapeze<T>>();
    } else {
        std::cout << "Invalid code.\n";
        return;
    }

    std::cout << "Please, enter 4 coordinades: \n";
    std::cin >> *rec;
    figures.addFigure(rec, figures.size());
}


template <Number T>
void calc_figure_func(const FigureArray<T>& figures) {
    size_t index = 0;

    std::cout << "Please, enter index of figure that you'd like to work with: ";
    std::cin >> index;

    if (figures.size() <= index) {
        std::cout << "Index is out of bounds!\n";
        return;
    }

    int code = -1;

    std::cout << "Please, pick which function you'd like to calc:\n";

    std::cout << 
    "1. Geometric center.\n" << 
    "2. Square.\n";

    std::cin >> code;

    if (code == 1) {
        std::cout << "Geometric center of figure: " << figures[index]->geometricCenter() << "\n";
    } else if (code == 2) {
        std::cout << "Square of figure: " << double(*figures[index]) << "\n";
    } else {
        std::cout << "Invalid code.\n";
        return;
    }
}

template <Number T>
void calc_sum_square(const FigureArray<T>& figures) {
    std::cout << "Summary square is: " << figures.summarySquare() << "\n";
}

template <Number T>
void delete_figure(FigureArray<T>& figures) {
    size_t index = 0;

    std::cout << "Please, enter index: ";
    std::cin >> index;

    if (figures.size() <= index) {
        std::cout << "Index is out of bounds!\n";
    }

    figures.eraseFigures(index, index + 1);
}

#endif