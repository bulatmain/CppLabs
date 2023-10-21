#ifndef FIGURE_H

#define FIGURE_H

#include <iostream>
#include <utility>

#include "lib/flat_vector.h"

class Figure {
public:
    virtual flat_vector geometricCenter() const = 0;

    virtual double square() const noexcept = 0;

    virtual operator double() const noexcept = 0;

    virtual std::istream& write_from_stream(std::istream&) = 0;

    virtual std::ostream& print_in_stream(std::ostream&) const = 0;

    virtual ~Figure() = 0;
};

std::istream& operator>> (std::istream& in, Figure& f);

std::ostream& operator<< (std::ostream& out, const Figure& f);

#endif