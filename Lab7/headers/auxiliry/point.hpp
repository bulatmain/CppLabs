#ifndef POINT_H

#define POINT_H

#include <cmath>
#include <string>

#include "declarations/declarations.hpp"

namespace lab7 {

    template <Number T>
    struct point {
        T x;
        T y;

        std::string to_str() {
            return "{ " + std::to_string(x) + ", " + std::to_string(y) + " }";
        }
    };

    template <Number T>
    T sqr(const T& v) {
        return v * v;
    }

    template <Number T>
    double distance(const point<T>& a, const point<T>& b) {
        return std::sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
    }
};

#endif