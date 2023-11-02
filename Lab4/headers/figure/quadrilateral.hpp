#ifndef QUADRILATERAL_H

#define QUADRILATERAL_H

// --------------- HEADER ---------------

#include <cmath>
#include <vector>
#include <list>

#include "figure.hpp"

template <Number T>
class Quadrilateral : public Figure<T> {

public:
    flat_vector<T> p1;
    flat_vector<T> p2;
    flat_vector<T> p3;
    flat_vector<T> p4;

// Constructors 
    Quadrilateral();

    Quadrilateral(const std::initializer_list<flat_vector<T>>& list);

// Calculation functions

    virtual flat_vector<T> geometricCenter() const override;

    virtual double square() const noexcept override;

    virtual operator double() const noexcept override;

// Comparation operators

    bool operator== (const Quadrilateral& other) const noexcept; 

// Stream operators

    virtual std::istream& write_from_stream(std::istream& in);

    virtual std::ostream& print_in_stream(std::ostream& out) const;
    
    virtual ~Quadrilateral() = default;

};

template <Number T>
std::vector<flat_vector<T>> find_corresponding(const std::vector<flat_vector<T>>& sides, std::list<flat_vector<T>>& applicants);

template <Number T>
bool angles_correspond(const std::vector<flat_vector<T>>& sides, const std::vector<flat_vector<T>>& matches);

template <Number Type>
class GeometricCenterCalculator {
public:
    const flat_vector<Type>& A;
    const flat_vector<Type>& B;
    const flat_vector<Type>& C;
    const flat_vector<Type>& D;
    flat_vector<Type> M;
    flat_vector<Type> T;
    flat_vector<Type> L;
    flat_vector<Type> P;
    flat_vector<Type> K;
    flat_vector<Type> S;

    GeometricCenterCalculator(const flat_vector<Type>& A,
                              const flat_vector<Type>& B,
                              const flat_vector<Type>& C,
                              const flat_vector<Type>& D);

    flat_vector<Type> calculate();

    flat_vector<Type> calcT(const flat_vector<Type>& A, 
                         const flat_vector<Type>& B) const;

};

// --------------- HEADER ---------------


// --------------- IMPLEMENTATION ---------------

#include <algorithm>
#include <exception>

// Quadrilateral
template <Number T>
Quadrilateral<T>::Quadrilateral() {}
template <Number T>
Quadrilateral<T>::Quadrilateral(const std::initializer_list<flat_vector<T>>& list) {
    if (list.size() == 4) {
        auto p = list.begin();
        p1 = *p;
        p2 = *(++p);
        p3 = *(++p);
        p4 = *(++p);
    } else {
        throw std::invalid_argument("Error: (in quadrilateral.h: 17) Quadrilateral(std::initializer_list<flat_vector<T>>&) takes 4 points in flat_vector<T>!\n");
    }
}

template <Number T>
flat_vector<T> Quadrilateral<T>::geometricCenter() const {
    GeometricCenterCalculator gcc(p1, p2, p3, p4);
    try {
        flat_vector<T> r = gcc.calculate();
        return r;
    } catch(const std::logic_error& e) {
        throw e;
    }
}
template <Number T>
double Quadrilateral<T>::square() const noexcept {
    flat_vector<T> a = p2 - p1;
    flat_vector<T> b = p3 - p2;
    flat_vector<T> c = p4 - p3;
    flat_vector<T> d = p1 - p4;
    return triangle_square(a, b) + triangle_square(c, d);
}
template <Number T>
Quadrilateral<T>::operator double() const noexcept {
    return square();
}
template <Number T>
std::istream& Quadrilateral<T>::write_from_stream(std::istream& in) {
    in >> p1 >> p2 >> p3 >> p4;
    return in;
}
template <Number T>
std::ostream& Quadrilateral<T>::print_in_stream(std::ostream& out) const {
    out << '(' << p1 << ", "
               << p2 << ", "
               << p3 << ", "
               << p4 << ')';
    return out;
}
template <Number T>
bool Quadrilateral<T>::operator== (const Quadrilateral& other) const noexcept {
    std::vector<flat_vector<T>> sides {
        p2 - p1,
        p3 - p2,
        p4 - p3,
        p1 - p4
    };

    std::list<flat_vector<T>> applicants {
        other.p2 - other.p1,
        other.p3 - other.p2,
        other.p4 - other.p3,
        other.p1 - other.p4
    };

    try {
        std::vector<flat_vector<T>> matches = find_corresponding(sides, applicants);

        return angles_correspond(sides, matches);
    } catch(...) {
        return false;
    }
}    
template <Number T>
std::vector<flat_vector<T>> find_corresponding(const std::vector<flat_vector<T>>& sides, std::list<flat_vector<T>>& applicants) {
    std::vector<flat_vector<T>> matches(4);
    for (uint8_t i = 0; i < 4; ++i) {
        auto applicant = applicants.begin();
        while (applicant != applicants.end() &&
               sides[i].len() != applicant->len()) {
            ++applicant;
        }
        if (applicant == applicants.end()) {
            throw std::logic_error("Sides do not match");
        } else {
            matches[i] = *applicant;
            applicants.erase(applicant);
        }
    }
    return matches;
}
template <Number T>
bool angles_correspond(const std::vector<flat_vector<T>>& sides, const std::vector<flat_vector<T>>& matches) {
    bool result = 
            angle(sides[0], sides[1]) == angle(matches[0], matches[1]) &&
            angle(sides[1], sides[2]) == angle(matches[1], matches[2]) &&
            angle(sides[2], sides[3]) == angle(matches[2], matches[3]) &&
            angle(sides[3], sides[0]) == angle(matches[3], matches[0]);

    return result;
}
template <Number Type>
GeometricCenterCalculator<Type>::GeometricCenterCalculator(
        const flat_vector<Type>& A,
        const flat_vector<Type>& B,
        const flat_vector<Type>& C,
        const flat_vector<Type>& D) : A(A), B(B), C(C), D(D) {}



// GeometricCenterCalculator
template <Number K>
flat_vector<K> GeometricCenterCalculator<K>::calculate() {
    // 1. 
    M = intersection(A, C, B, D);
    // 2.
    T = calcT(A, C);
    L = calcT(B, D);
    // 3.
    P = (A + C) * 0.5;
    K = (B + D) * 0.5;
    // 4. 
    try {
        S = intersection(P, L, K, T);
        return S;
    } catch(const std::logic_error& e) {
        throw std::logic_error("Can not calculate geometric center of gegenerate quadrilateral");
    }
}
template <Number Type>
flat_vector<Type> GeometricCenterCalculator<Type>::calcT(
            const flat_vector<Type>& A,
            const flat_vector<Type>& C) const {
    flat_vector<Type> T;
    if ((M - A).len() < (M - C).len()) {
        T = C + (A - M);
    } else {
        T = A + (C - M);
    }
    return T;
}

// --------------- IMPLEMENTATION ---------------

#endif