#include "lib/octal.h"

#include <string>

#define min(a, b) ((a) < (b) ? (a) : (b))

// Constructor

Octal::Octal() {
    this->size = 1;
    this->array = new OctalDigit[1];
}

size_t sizeByNumber(size_t k) {
    size_t size = 0;
    while (k) {
        k >>= 3;
        ++size;
    }
    return size;
}

Octal::Octal(size_t n) {
    if (n == 0) {
        size = 1;
        array = new OctalDigit[1];
    } else {
        size = sizeByNumber(n);
        array = new OctalDigit[size];
        size_t count = 0;
        while (n) {
            array[count++] = OctalDigit(n % 8);
            n >>= 3; 
        }
    }
}

Octal::Octal(size_t size, const OctalDigit& d) {
    this->size = size;
    this->array = new OctalDigit[size];
    for (size_t i = 0; i < size; ++i) {
        this->array[i] = d;
    }
}

Octal::Octal(const std::initializer_list<OctalDigit>& t) {
    this->array = new OctalDigit[t.size()];
    this->size = 0;
    for (const auto& d : t) {
        this->array[t.size() - ++this->size] = d;
    }
}

Octal::Octal(const std::string& t) {
    this->array = new OctalDigit[t.size()];
    this->size = 0;
    for (const auto& d : t) {
        this->array[t.size() - ++this->size] = d;
    }
}

Octal::Octal(const Octal& other) {
    copy(other);
}

Octal::Octal(Octal&& other) noexcept {
    move(std::move(other));
}

// Assign

Octal& Octal::operator =(const Octal& other) {
    free();
    copy(other);
    return *this;
}

Octal& Octal::operator =(Octal&& other) {
    free();
    move(std::move(other));
    return *this;
}

// Arithmetic

void addDigits(unsigned char& biggest, const unsigned char& smallest, unsigned char& inMind) {
        biggest += smallest + inMind - '0' * 3;
        inMind = biggest / 8 + '0';
        biggest = (biggest % 8) + '0';
}

void addSmallestToBiggest(OctalDigit* smallest, OctalDigit* biggest, 
                            OctalDigit& inMind, size_t smallest_size) {
    for (size_t i = 0; i < smallest_size; ++i) {
        addDigits(biggest[i].c, smallest[i].c, inMind.c);
    }
}

void resizeArray(OctalDigit*& array, size_t size_old, size_t size_new) {
    if (size_old == size_new) {
        return;
    }

    OctalDigit* temp = new OctalDigit[size_new];
    for (size_t j = 0; j < min(size_old, size_new); ++j) {
        temp[j] = array[j];
    }
    delete[] array;
    array = temp;
}

void addInMind(OctalDigit*& biggest, OctalDigit& inMind,
               size_t start, size_t& biggest_size) {
    size_t i = start;
    while ((i < biggest_size) && (inMind != '0')) {
        addDigits(biggest[i++].c, '0', inMind.c);
    }
    if (inMind != '0') {
        resizeArray(biggest, i, i + 1);
        biggest_size = i + 1;
        biggest[i].c = inMind.c;
    }
}

Octal& Octal::operator +=(const Octal& other) {
    Octal biggest = (*this < other ? other : *this);
    const Octal& smallest = (*this < other ? *this : other);

    OctalDigit inMind('0');

    addSmallestToBiggest(smallest.array, biggest.array,
                         inMind, smallest.size);

    addInMind(biggest.array, inMind, smallest.size, biggest.size);

    return *this = biggest;
}

Octal Octal::operator +(const Octal& other) const {
    Octal temp = *this;
    temp += other;
    return temp; 
}

void substractOneFromOlders(OctalDigit*& biggest, size_t& i) {
    while (biggest[i + 1] == '0') {
        biggest[i + 1].c = '7';
        ++i;
    }
    biggest[i + 1].c -= 1;
}

void substractArrays(OctalDigit*& biggest, OctalDigit* const smallest, size_t smallest_size) {
    size_t i = 0;
    while (i < smallest_size) {
        if (biggest[i].c < smallest[i].c) {
            biggest[i].c += ('8' - smallest[i].c);
            substractOneFromOlders(biggest, i);
        } else {
            biggest[i].c -= smallest[i].c - '0';
        }
        ++i;
    }
}

void resizeAfterSubstraction(OctalDigit*& array, size_t& size) {
    size_t size_new = size;
    while (array[size_new - 1].c == '0') {
        --size_new;
    }
    if (size_new == 0) {
        size_new = 1;
    }
    resizeArray(array, size, size_new);
    size = size_new;
}

Octal& Octal::operator -=(const Octal& other) {
    if (*this < other) {
        throw std::invalid_argument("Argument must be less than object!\n");
    } else {
        substractArrays(this->array, other.array, other.size);
        resizeAfterSubstraction(this->array, this->size);
    }
    return *this;
}

Octal Octal::operator -(const Octal& other) const {
    Octal temp = *this;
    temp -= other;
    return temp; 
}

// Comparation

bool sameArrays(OctalDigit* a, OctalDigit* b, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool Octal::operator ==(const Octal& other) const {
    if (this->size == other.size) {
        return sameArrays(this->array, other.array, this->size);
    } else {
        return false;
    }
}

bool firstArrayLessThanSecond(OctalDigit* first, OctalDigit* second, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        size_t index = size - i - 1;
        if (first[index] < second[index]) {
            return true;
        }
    }
    return false;
}

bool Octal::operator <(const Octal& other) const {
    if (this->size == other.size) {
        return firstArrayLessThanSecond(this->array, other.array, this->size);
    } else {
        return this->size < other.size;
    }
}

bool Octal::operator !=(const Octal& other) const {
    return !(*this == other);
}

bool Octal::operator <=(const Octal& other) const {
    return (*this < other) || (*this == other);
}

bool Octal::operator >(const Octal& other) const {
    return !(*this <= other);
}

bool Octal::operator >=(const Octal& other) const {
    return !(*this < other);
}

// Getters

size_t Octal::length() const {
    return this->size;
}

// Auxiliary

void Octal::copy(const Octal& other) {
    this->size = other.size;
    this->array = new OctalDigit[size];
    for (size_t i = 0; i < other.size; ++i) {
        this->array[i] = other.array[i];
    }
}

void Octal::move(Octal&& other) {
    size = other.size;
    array = other.array;

    other.size = 0;
    other.array = nullptr;
}

void Octal::free() {
    if (array == nullptr) {
        delete array;
    }
    size = 0;
    array = nullptr;
}

// Destructor

Octal::~Octal() {
    free();
}


std::ostream& operator <<(std::ostream& out, const Octal& octal) {
    const auto& a = octal.array;
    for (size_t i = 0; i < octal.size; ++i) {
        out << (a + octal.size - i - 1)->c;
    }
    return out;
}

#undef min