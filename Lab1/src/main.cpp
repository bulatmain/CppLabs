#include <iostream>

#include "lib/header.hpp"

int main() {
    std::string input;

    std::cout << "Please, input sequence of curly brakets: ";

    std::cin >> input;

    bool result = validateBraketString(input);

    if (result) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    return 0;
}