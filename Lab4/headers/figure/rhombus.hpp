#ifndef RHOMBUS_H

#define RHOMBUS_H

#include "quadrilateral.hpp"

template <Number T>
class Rhombus : public Quadrilateral<T> {

public:
    Rhombus();
    Rhombus(const std::initializer_list<flat_vector<T>>& list);
    
};

template <Number T>
Rhombus<T>::Rhombus() : Quadrilateral<T>() {}

template <Number T>
Rhombus<T>::Rhombus(const std::initializer_list<flat_vector<T>>& list) : Quadrilateral<T>(list) {}

#endif