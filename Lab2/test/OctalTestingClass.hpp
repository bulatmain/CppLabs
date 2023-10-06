#ifndef OCTALTESTINGCLASS_H

#define OCTALTESTINGCLASS_H

#include <iostream>

#include "lib/octal.h"

class OctalTest : public Octal {
public:
    OctalTest(const Octal& octal) : Octal(octal) {}

    OctalTest() : Octal() {}

    OctalTest(size_t n) : Octal(n) {}

    OctalTest(const std::initializer_list<OctalDigit>& t)
        : Octal(t) {}

    OctalTest(size_t n, const OctalDigit& d) 
        : Octal(n, d) {}

    OctalTest(const std::string& t)
        : Octal(t) {}

    OctalTest(const OctalTest& other) 
        : Octal(other) {}

    OctalTest(OctalTest&& other) noexcept
        : Octal(std::move(other)) {}

// Operators

    OctalTest& operator =(const OctalTest& other) {
        Octal::operator=(other); 
        return *this;
    }

    OctalTest& operator =(OctalTest&& other) {
        Octal::operator=(std::move(other)); 
        return *this;
    }
    
// Public Getters

    OctalDigit* getArray() const {
        return this->array;
    }

    size_t getSize() const {
        return this->size;
    }

    OctalDigit*& getArray() {
        return this->array;
    }

    size_t& getSize() {
        return this->size;
    }

    ~OctalTest() {}
};


#endif