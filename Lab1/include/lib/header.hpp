#ifndef HEADER_H

#define HEADER_H

#include <cinttypes>
#include <string>

bool validateBraketString(const std::string& s) {
    // if braket opens -> count++;
    // else            -> count--;
    // if string is valid then count should be equal to 0
    // if at any moment count < 0 -> string is not valid
    int32_t count = 0;

    for (char c : s) {
        if (count < 0) {
            break;
        } else {
            count += (c == '(' ? 1 : -1);
        }
    }

    return count == 0;
}

#endif