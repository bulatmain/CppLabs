#ifndef RECTANGLE_H

#define RECTANGLE_H

#include "quadrilateral.h"

class Rectangle : public Quadrilateral {

public:
    Rectangle();
    Rectangle(const std::initializer_list<flat_vector>& list);
    
};

#endif