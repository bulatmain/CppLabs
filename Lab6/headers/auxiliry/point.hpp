#ifndef POINT_H

#define POINT_H

#include <type_traits>
#include <stdexcept>
#include <concepts>
#include <cmath>

namespace lab6 {
    template <typename T>
    concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <Number T>
    struct point {
        T x;
        T y;
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