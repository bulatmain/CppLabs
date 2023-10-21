#include <algorithm>
#include <exception>

#include "lib/quadrilateral.h"

// Quadrilateral

Quadrilateral::Quadrilateral() {}

Quadrilateral::Quadrilateral(const std::initializer_list<flat_vector>& list) {
    if (list.size() == 4) {
        auto p = list.begin();
        p1 = *p;
        p2 = *(++p);
        p3 = *(++p);
        p4 = *(++p);
    } else {
        throw std::invalid_argument("Error: (in quadrilateral.h: 17) Quadrilateral(std::initializer_list<flat_vector>&) takes 4 points in flat_vector!\n");
    }
}


flat_vector Quadrilateral::geometricCenter() const {
    GeometricCenterCalculator gcc(p1, p2, p3, p4);
    try {
        flat_vector r = gcc.calculate();
        return r;
    } catch(const std::logic_error& e) {
        throw e;
    }
}

double Quadrilateral::square() const noexcept {
    flat_vector a = p2 - p1;
    flat_vector b = p3 - p2;
    flat_vector c = p4 - p3;
    flat_vector d = p1 - p4;
    return triangle_square(a, b) + triangle_square(c, d);
}

Quadrilateral::operator double() const noexcept {
    return square();
}

std::istream& Quadrilateral::write_from_stream(std::istream& in) {
    in >> p1 >> p2 >> p3 >> p4;
    return in;
}

std::ostream& Quadrilateral::print_in_stream(std::ostream& out) const {
    out << '(' << p1 << ", "
               << p2 << ", "
               << p3 << ", "
               << p4 << ')';
    return out;
}

bool Quadrilateral::operator== (const Quadrilateral& other) const noexcept {
    std::vector<flat_vector> sides {
        p2 - p1,
        p3 - p2,
        p4 - p3,
        p1 - p4
    };

    std::list<flat_vector> applicants {
        other.p2 - other.p1,
        other.p3 - other.p2,
        other.p4 - other.p3,
        other.p1 - other.p4
    };

    try {
        std::vector<flat_vector> matches = find_corresponding(sides, applicants);

        return angles_correspond(sides, matches);
    } catch(...) {
        return false;
    }
}    

std::vector<flat_vector> find_corresponding(const std::vector<flat_vector>& sides, std::list<flat_vector>& applicants) {
    std::vector<flat_vector> matches(4);
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

bool angles_correspond(const std::vector<flat_vector>& sides, const std::vector<flat_vector>& matches) {
    bool result = 
            angle(sides[0], sides[1]) == angle(matches[0], matches[1]) &&
            angle(sides[1], sides[2]) == angle(matches[1], matches[2]) &&
            angle(sides[2], sides[3]) == angle(matches[2], matches[3]) &&
            angle(sides[3], sides[0]) == angle(matches[3], matches[0]);

    return result;
}

GeometricCenterCalculator::GeometricCenterCalculator(
        const flat_vector& A,
        const flat_vector& B,
        const flat_vector& C,
        const flat_vector& D) : A(A), B(B), C(C), D(D) {}



// GeometricCenterCalculator

flat_vector GeometricCenterCalculator::calculate() {
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

flat_vector GeometricCenterCalculator::calcT(
            const flat_vector& A,
            const flat_vector& C) const {
    flat_vector T;
    if ((M - A).len() < (M - C).len()) {
        T = C + (A - M);
    } else {
        T = A + (C - M);
    }
    return T;
}