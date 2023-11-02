#include <iostream>
#include "auxiliary/auxiliary.hpp"


int main() {

    FigureArray<double> figures;

    int code = 0;

    while (true) {
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
