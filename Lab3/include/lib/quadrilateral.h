#ifndef QUADRILATERAL_H

#define QUADRILATERAL_H

#include <cmath>
#include <vector>
#include <list>

#include "figure.h"

class Quadrilateral : public Figure {

public:
    flat_vector p1;
    flat_vector p2;
    flat_vector p3;
    flat_vector p4;

// Constructors 
    Quadrilateral();

    Quadrilateral(const std::initializer_list<flat_vector>& list);

// Calculation functions

    virtual flat_vector geometricCenter() const override;

    virtual double square() const noexcept override;

    virtual operator double() const noexcept override;

// Comparation operators

    bool operator== (const Quadrilateral& other) const noexcept; 

// Stream operators

    virtual std::istream& write_from_stream(std::istream& in);

    virtual std::ostream& print_in_stream(std::ostream& out) const;
    
    virtual ~Quadrilateral() = default;

};

std::vector<flat_vector> find_corresponding(const std::vector<flat_vector>& sides, std::list<flat_vector>& applicants);

bool angles_correspond(const std::vector<flat_vector>& sides, const std::vector<flat_vector>& matches);

class GeometricCenterCalculator {
public:
    const flat_vector& A;
    const flat_vector& B;
    const flat_vector& C;
    const flat_vector& D;
    flat_vector M;
    flat_vector T;
    flat_vector L;
    flat_vector P;
    flat_vector K;
    flat_vector S;

    GeometricCenterCalculator(const flat_vector& A,
                              const flat_vector& B,
                              const flat_vector& C,
                              const flat_vector& D);

    flat_vector calculate();

    flat_vector calcT(const flat_vector& A, 
                      const flat_vector& B) const;

};

#endif