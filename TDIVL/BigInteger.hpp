#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include <istream>
#include <deque>
#include <string>

struct IntegerDivisionResult;

class BigInteger {
public:
    using uint64 = unsigned long long;
    using uint32 = unsigned int;

    BigInteger();
    BigInteger(uint64 a);
    BigInteger(const std::string& a);

    BigInteger& operator *= (const uint64& rhs);
    BigInteger& operator /= (const uint64& y);

    friend BigInteger operator + (const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator - (const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator * (const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator / (const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator % (const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator == (const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator < (const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator > (const BigInteger& lhs, const BigInteger& rhs);
    friend std::istream& operator >> (std::istream& stream, BigInteger& number);
    friend std::ostream& operator << (std::ostream& stream, const BigInteger& number);
    friend IntegerDivisionResult divideWithRemainder(BigInteger lhs, BigInteger rhs);

private:
    using constDequeIterator = std::deque<uint64>::const_iterator;

    std::deque<uint64> parts;
    bool sign;

    static uint64 __normalizeNumbers(BigInteger& a, BigInteger& b, uint64 base);
    static BigInteger __subtract(const BigInteger& a, const BigInteger& b);
    static BigInteger __add(const BigInteger& a, const BigInteger& b);
    static bool __greaterThanOrEqualAbs(const BigInteger& a, const BigInteger& b);
    
    // Copy part
    BigInteger(const constDequeIterator&, const constDequeIterator&);

    bool isZero() const;
    void shift(uint32 offset);
    BigInteger copyShift(uint32 offset) const;
    BigInteger karatsubaMultiply(const BigInteger& x, const BigInteger& y) const;
};

struct IntegerDivisionResult {
    BigInteger quotient;
    BigInteger remainder;

    IntegerDivisionResult(const BigInteger& _quotient, const BigInteger& _remainder): quotient(_quotient), remainder(_remainder) {}
};

#endif // !BIG_INTEGER_HPP
