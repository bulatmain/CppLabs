
#ifndef PRIMITIVE_ARRAY
#define PRIMITIVE_ARRAY

#include <iostream>
#include <concepts>
#include <memory>

template <class T>
concept Arrayable = std::is_default_constructible<T>::value;

template <Arrayable T>
class Array
{
public:
    Array();

    Array(size_t size);

    Array(const std::initializer_list<T> &t);

    Array(const Array &other);

    Array(Array &&other) noexcept;

    Array& operator=(const Array& other);

    Array& operator=(Array&& other);

    T& operator[](size_t index);

    T operator[](size_t index) const;

    size_t size() const;

    ~Array() noexcept;

protected:
    void copy(const Array& other);
    void move(Array&& other);

protected:
    size_t _size;
    std::shared_ptr<T[]> _array;
};

template <Arrayable T> 
Array<T>::Array() : _size(0), _array{nullptr} {}

template <Arrayable T>
Array<T>::Array(size_t size) : _size(size) {
    _array = std::shared_ptr<T[]>(new T[size]);
}

template <Arrayable T> 
Array<T>::Array(const std::initializer_list<T> &t) : Array(t.size()) {
    size_t i{0};

    for (auto &c : t)
        _array[i++] = c;
}

template <Arrayable T>
void Array<T>::copy(const Array<T>& other) {
    _size = other._size;
    _array = std::shared_ptr<T[]>(new T[_size]);

    for (size_t i{0}; i < _size; ++i)
        _array[i] = other._array[i];
}

template <Arrayable T>
void Array<T>::move(Array<T>&& other) {
    this->_size = other._size;
    this->_array = other._array;

    other._size = 0;
    other._array = nullptr;
}


template <Arrayable T> 
Array<T>::Array(const Array &other) {
    copy(other);
}

template <Arrayable T> 
Array<T>::Array(Array &&other) noexcept {
    move(std::move(other));
}

template <Arrayable T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    copy(other);
    return *this;
}

template <Arrayable T>
Array<T>& Array<T>::operator=(Array<T>&& other) {
    move(other);
    return *this;
}


template <Arrayable T>
T& Array<T>::operator[](size_t index) {
    if (_size <= index) {
        throw std::invalid_argument("Trying access arrray's element out of it's bounds.");
    } else {
        return _array[index];
    }
}

template <Arrayable T>
T Array<T>::operator[](size_t index) const {
    return (*this)[index];
}

template <Arrayable T>
size_t Array<T>::size() const {
    return _size;
}

template <Arrayable T>
Array<T>::~Array() noexcept {}

#endif