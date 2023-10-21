#ifndef TRAPEZE_H

#define TRAPEZE_H

#include "rectangle.h"

class Trapeze : public Quadrilateral {

public:
    Trapeze();
    Trapeze(const std::initializer_list<flat_vector>& list);
};

#endif