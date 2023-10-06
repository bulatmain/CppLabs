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

    void copy(const Octal& other);

    void move(Octal&& other);

    void free();

public:

// Destructor

    virtual ~Octal() noexcept;

// Friends
protected:
    friend std::ostream& operator <<(std::ostream& out, const Octal& octal);

};



#endif