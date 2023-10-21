#ifndef RHOMBUS_H

#define RHOMBUS_H

#include "quadrilateral.h"

class Rhombus : public Quadrilateral {

public:
    Rhombus();
    Rhombus(const std::initializer_list<flat_vector>& list);
    
};

#endif