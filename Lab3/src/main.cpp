#include <iostream>

#include "lib/figure.h"
#include "lib/rectangle.h"
#include "lib/rhombus.h"
#include "lib/trapeze.h"

void add_figure(std::vector<Figure*>& figures);

void calc_figure_func(const std::vector<Figure*>& figures);

void calc_sum_square(const std::vector<Figure*>& figures);

void delete_figure(std::vector<Figure*>& figures);


int main() {

    std::vector<Figure*> figures;

    int code = -1;

    while (code != 0) {
        std::cout << "Please, pick one of these options:\n";
        std::cout <<
        "1. Add figure.\n" <<
        "2. Calculate figure function.\n" <<
        "3. Calculate summary square.\n" << 
        "4. Delete figure.\n" <<
        "5. Exit.\n";

        std::cin >> code;

        if (code == 1) {
            add_figure(figures);
        } else if (code == 2) {
            calc_figure_func(figures);
        } else if (code == 3) {
            calc_sum_square(figures);
        } else if (code == 4) {
            delete_figure(figures);
        } else if (code == 5) {
            break;
        } else {
            std::cout << "Invalid code.\n";
        }
    }

    return 0;
}


void add_figure(std::vector<Figure*>& figures) {
    int code = -1;

    std::cout << "Please, pick which figure you'd like to add:\n";

    std::cout << 
    "1. Rectangle.\n" << 
    "2. Rhombus.\n" << 
    "3. Trapeze.\n";

    std::cin >> code;

    Quadrilateral* rec;

    if (code == 1) {
        rec = new Rectangle();     
    } else if (code == 2) {
        rec = new Rhombus();
    } else if (code == 3) {
        rec = new Trapeze();
    } else {
        std::cout << "Invalid code.\n";
        return;
    }

    std::cout << "Please, enter 4 coordinades: \n";
    std::cin >> *rec;
    figures.push_back(rec);   
}


void calc_figure_func(const std::vector<Figure*>& figures) {
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

void calc_sum_square(const std::vector<Figure*>& figures) {
    double sum = 0;

    for (auto& p : figures) {
        sum += double(*p);
    }

    std::cout << "Summary square is: " << sum << "\n";
}

void delete_figure(std::vector<Figure*>& figures) {
    size_t index = 0;

    std::cout << "Please, enter index: ";
    std::cin >> index;

    if (figures.size() <= index) {
        std::cout << "Index is out of bounds!\n";
    }

    Figure* to_delete = figures[index];
    figures.erase(figures.begin() + index);
    delete to_delete;
}