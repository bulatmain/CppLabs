#include "lib/figure.h"

std::istream& operator>> (std::istream& in, Figure& f) {
    return f.write_from_stream(in);
}

std::ostream& operator<< (std::ostream& out, const Figure& f) {
    return f.print_in_stream(out);
}

Figure::~Figure() {}