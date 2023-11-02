#ifndef FIGURE_ARRAY_H
#define FIGURE_ARRAY_H

#include "prim_array/primitive_array.hpp"
#include "figure/figure.hpp"

namespace lab4 {
    template <Number T>
    using fshared_ptr = std::shared_ptr<Figure<T>>;

    template <Number T>
    class FigureArray : public Array<fshared_ptr<T>> {
    public:
        FigureArray();
        FigureArray(size_t size);
        FigureArray(const std::initializer_list<fshared_ptr<T>> &t);
        FigureArray(const FigureArray &other);
        FigureArray(FigureArray &&other) noexcept;

        FigureArray& operator=(const FigureArray& other);
        FigureArray& operator=(FigureArray&& other);

        T summarySquare() const;

        // [0, 1, ..., l - 1, l, ..., r, ... _size - 1]
    // ->  [0, 1, ..., l - 1, ..., _size - r - l - 1]
        void eraseFigures(size_t l, size_t r);

        // [0, 1, ..., index, ..., _size - 1]
        //   new element |      | 
        //               v      v old element
    // ->  [0, 1, ..., index', index + 1, ..., _size]
        void addFigure(fshared_ptr<T> figure_ptr, size_t index);
    };
}

template <Number T>
lab4::FigureArray<T>::FigureArray() : Array<lab4::fshared_ptr<T>>() {}
template <Number T>
lab4::FigureArray<T>::FigureArray(size_t size) : Array<lab4::fshared_ptr<T>>(size) {}
template <Number T>
lab4::FigureArray<T>::FigureArray(const std::initializer_list<lab4::fshared_ptr<T>> &t) : Array<lab4::fshared_ptr<T>>(t) {}
template <Number T>
lab4::FigureArray<T>::FigureArray(const FigureArray &other) : Array<lab4::fshared_ptr<T>>(other) {}
template <Number T>
lab4::FigureArray<T>::FigureArray(FigureArray &&other) noexcept : Array<lab4::fshared_ptr<T>>(std::move(other)) {}

template <Number T>
lab4::FigureArray<T>& lab4::FigureArray<T>::operator=(const FigureArray<T>& other) {
    this->copy(other);
    return *this;
}

template <Number T>
lab4::FigureArray<T>& lab4::FigureArray<T>::operator=(FigureArray<T>&& other) {
    this->move(std::move(other));
    return *this;
}


template <Number T>
T lab4::FigureArray<T>::summarySquare() const {
    T sum{};
    for (size_t i = 0; i < this->_size; ++i) {
        sum += this->_array[i]->square();
    }
    return sum;
}

template <Number T>
void lab4::FigureArray<T>::eraseFigures(size_t l, size_t r) {
    if (this->_size < r) {
        throw std::invalid_argument("Trying erase array's elements out of it's bounds");
    }
    size_t d = r - l;
    FigureArray<T> new_arr(this->_size - d);
    for (size_t i = 0; i < l; ++i) {
        new_arr[i] = this-> _array[i];
    }
    for (size_t i = l; i < this->_size - d; ++i) {
        new_arr[i] = this->_array[i + d];
    }
    *this = std::move(new_arr);
}

template <Number T>
void lab4::FigureArray<T>::addFigure(fshared_ptr<T> figure_ptr, size_t index) {
    if (this->_size < index) {
        throw std::invalid_argument("Trying access arrray's element out of it's bounds.");
    }
    FigureArray<T> new_arr(this->_size + 1);
    for (size_t i = 0; i < index; ++i) {
        new_arr[i] = this->_array[i];
    }
    new_arr[index] = figure_ptr;
    for (size_t i = index + 1; i < this->_size + 1; ++i) {
        new_arr[i] = this->_array[i - 1];
    }
    *this = std::move(new_arr);
}

#endif