#ifndef FIGURE_H

#define FIGURE_H

// --------------- HEADER ---------------

#include <iostream>
#include <utility>

#include "flat_vector/flat_vector.hpp"

template <Number T>
class Figure {
public:
    virtual flat_vector<T> geometricCenter() const = 0;

    virtual double square() const noexcept = 0;

    virtual operator double() const noexcept = 0;

    virtual std::istream& write_from_stream(std::istream&) = 0;

    virtual std::ostream& print_in_stream(std::ostream&) const = 0;

    virtual ~Figure() = 0;
};

template <Number T>
std::istream& operator>> (std::istream& in, Figure<T>& f);

template <Number T>
std::ostream& operator<< (std::ostream& out, const Figure<T>& f);

// --------------- HEADER ---------------

// --------------- IMPLEMENTATION ---------------

template <Number T>
std::istream& operator>> (std::istream& in, Figure<T>& f) {
    return f.write_from_stream(in);
}


template <Number T>
std::ostream& operator<< (std::ostream& out, const Figure<T>& f) {
    return f.print_in_stream(out);
}

template <Number T>
Figure<T>::~Figure() {}

// --------------- IMPLEMENTATION ---------------

#endif