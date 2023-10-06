#ifndef OCTALDIGIT_H

#define OCTALDIGIT_H

class OctalDigit {
public:
    unsigned char c;

public:
// Constructor
    OctalDigit();

    OctalDigit(unsigned char c);

    OctalDigit(const OctalDigit& other);

// Operators

    OctalDigit& operator =(const OctalDigit& other);

    OctalDigit operator +(const OctalDigit& other) const;

    OctalDigit operator -(const OctalDigit& other) const;

    OctalDigit& operator +=(const OctalDigit& other);

    OctalDigit& operator -=(const OctalDigit& other);

    OctalDigit operator +(unsigned char c) const;

    OctalDigit operator -(unsigned char c) const;

    OctalDigit& operator +=(unsigned char c);

    OctalDigit& operator -=(unsigned char c);

    bool operator ==(const OctalDigit& other) const;

    bool operator !=(const OctalDigit& other) const;

    bool operator <(const OctalDigit& other) const;

    bool operator <=(const OctalDigit& other) const;

    bool operator >(const OctalDigit& other) const;

    bool operator >=(const OctalDigit& other) const;

    friend std::ostream& operator <<(std::ostream& out, const OctalDigit& d);

// Auxiliary

    void setChar(unsigned char c);

};

#endif
