#include <stdexcept>
#include "lib/octalDigit.h"

OctalDigit::OctalDigit() : OctalDigit('0') {}

OctalDigit::OctalDigit(unsigned char c) {
    setChar(c);
}

OctalDigit::OctalDigit(const OctalDigit& other) {
    *this = other;
}

OctalDigit& OctalDigit::operator =(const OctalDigit& other) {
    setChar(other.c);
    return *this;
}

OctalDigit OctalDigit::operator +(const OctalDigit& other) const {
    OctalDigit res = *this;
    return res += other;
}

OctalDigit OctalDigit::operator -(const OctalDigit& other) const {
    OctalDigit res = *this;
    return res -= other;
}

OctalDigit& OctalDigit::operator +=(const OctalDigit& other) {
    return *this += (other.c - '0');
}

OctalDigit& OctalDigit::operator -=(const OctalDigit& other) {
    return *this -= (other.c - '0');
}

OctalDigit OctalDigit::operator +(unsigned char c) const {
    OctalDigit res = *this;
    return res += c;
}

OctalDigit OctalDigit::operator -(unsigned char c) const {
    OctalDigit res = *this;
    return res -= c;
}

OctalDigit& OctalDigit::operator +=(unsigned char c) {
    this->c += c;
    if ('7' < this->c) {
        this->c = (this->c % '8' + '0');
    }
    return *this;
}

OctalDigit& OctalDigit::operator -=(unsigned char c) {
    if (c + '0' <= this->c) {
        this->c -= c;
    } else {
        this->c += 8 - c;
    }
    return *this;
}


bool OctalDigit::operator ==(const OctalDigit& other) const {
    return this->c == other.c;
}

bool OctalDigit::operator !=(const OctalDigit& other) const {
    return !(*this == other);
}

bool OctalDigit::operator <(const OctalDigit& other) const {
    return this->c < other.c;
}

bool OctalDigit::operator <=(const OctalDigit& other) const {
    return (*this < other) || (*this == other);
}

bool OctalDigit::operator >(const OctalDigit& other) const {
    return !(*this <= other);
}

bool OctalDigit::operator >=(const OctalDigit& other) const {
    return !(*this < other);
}

std::ostream& operator <<(std::ostream& out, const OctalDigit& d) {
    out << d.c;
    return out;
}

void OctalDigit::setChar(unsigned char c) {
    if ('0' <= c && c <= '7') {
        this->c = c;
    } else if (0 <= c && c <= 7) {
        this->c = c + '0';
    } else {
        throw std::invalid_argument("No way to cast unsigned char to octal digit\n");
    }
}