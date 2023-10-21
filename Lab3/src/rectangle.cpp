#include "lib/rectangle.h"

Rectangle::Rectangle() : Quadrilateral() {}

Rectangle::Rectangle(const std::initializer_list<flat_vector>& list) : Quadrilateral(list) {}