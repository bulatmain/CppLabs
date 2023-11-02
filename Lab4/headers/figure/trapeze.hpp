#ifndef TRAPEZE_H

#define TRAPEZE_H

#include "quadrilateral.hpp"

template <Number T>
class Trapeze : public Quadrilateral<T> {

public:
    Trapeze();
    Trapeze(const std::initializer_list<flat_vector<T>>& list);
    
};

template <Number T>
Trapeze<T>::Trapeze() : Quadrilateral<T>() {}

template <Number T>
Trapeze<T>::Trapeze(const std::initializer_list<flat_vector<T>>& list) : Quadrilateral<T>(list) {}

#endif