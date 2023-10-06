#ifndef OCTAL_H

#define OCTAL_H

#include <iostream>
#include <string>

#include "octalDigit.h"

class Octal {
protected:
    OctalDigit* array;
    size_t size;

public:

// Constrcuctors

    Octal();

    Octal(size_t n);

    Octal(size_t size, const OctalDigit& d);

    Octal(const std::initializer_list<OctalDigit>& t);

    Octal(const std::string& t);

    Octal(const Octal& other);

    Octal(Octal&& other) noexcept;

// Operators

    // Assign

    Octal& operator =(const Octal& other);

    Octal& operator =(Octal&& other);

    // Arithmetic

    Octal operator +(const Octal& other) const;

    Octal& operator +=(const Octal& other);

    Octal operator -(const Octal& other) const; 

    Octal& operator -=(const Octal& other);

    // Comparation

    bool operator ==(const Octal& other) const;

    bool operator !=(const Octal& other) const;

    bool operator <(const Octal& other) const;

    bool operator <=(const Octal& other) const;

    bool operator >(const Octal& other) const;

    bool operator >=(const Octal& other) const;

// Getters

    size_t length() const;

// Auxiliary

private:
// For operators= and constructors

    void copy(const Octal& other);

    void move(Octal&& other);

    void free();

// For arithmetic

    // Plus

    void addDigits(unsigned char& biggest, const unsigned char& smallest, unsigned char& inMind);

    void addSmallestToBiggest(OctalDigit* smallest, OctalDigit* biggest, OctalDigit& inMind, size_t smallest_size);

    void resizeArray(OctalDigit*& array, size_t size_old, size_t size_new);

    void addInMind(OctalDigit*& biggest, OctalDigit& inMind, size_t start, size_t& biggest_size);

    // Minus

    void substractOneFromOlders(OctalDigit*& biggest, size_t& i);

    void substractArrays(OctalDigit*& biggest, OctalDigit* const smallest, size_t smallest_size);

    void resizeAfterSubstraction(OctalDigit*& array, size_t& size);

// For comparation

    bool sameArrays(OctalDigit* a, OctalDigit* b, size_t size) const;

    bool firstArrayLessThanSecond(OctalDigit* first, OctalDigit* second, size_t size) const;

public:

// Destructor

    virtual ~Octal() noexcept;

// Friends
protected:
    friend std::ostream& operator <<(std::ostream& out, const Octal& octal);

};



#endif