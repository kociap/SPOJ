#include "BigInteger.hpp"
#include <string>
#include <iomanip>

// Number is stored as chunks from left (least significant) to right (most significant)
// Aligned to the left

using uint64 = unsigned long long;
using int64 = long long;
constexpr uint64 MAX_DIGITS = 9;
constexpr uint64 WORD_VALUE_CAP = 1000000000;

BigInteger::BigInteger(): parts(1, 0), sign(false) {}

BigInteger::BigInteger(uint64 a) : parts(1, a), sign(false) {}

BigInteger::BigInteger(const std::string& a) : parts(a.size() / MAX_DIGITS + 1, 0), sign(false) {
    int64 firstDigitIndex = (a[0] == '-' ? 1 : 0);
    for (int64 i = a.size() - 1, k = 0; i >= firstDigitIndex; i -= MAX_DIGITS, ++k) {
        for (int64 j = (i - static_cast<int64>(MAX_DIGITS) + 1 >= firstDigitIndex ? i - MAX_DIGITS + 1 : firstDigitIndex); j <= i; ++j) {
            parts[k] *= 10;
            parts[k] += a[j] - 48;
        }
    }

    while (parts[parts.size() - 1] == 0) { // If too much storage space
        parts.pop_back();
    }
}

BigInteger::BigInteger(const constDequeIterator& begin, const constDequeIterator& end): parts(begin, end), sign(false) {
    if (parts.size() == 0) {
        parts.push_back(0);
    }
}

bool BigInteger::isZero() const {
    return parts.size() == 1 && parts[0] == 0;
}

uint64 max(uint64 a, uint64 b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

uint64 min(uint64 a, uint64 b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void BigInteger::shift(uint32 offset) {
    if (!isZero()) {
        for (int i = 0; i < offset; ++i) {
            parts.push_front(0);
        }
    }
}

BigInteger BigInteger::copyShift(uint32 offset) const {
    BigInteger a(*this);
    a.shift(offset);
    return a;
}

uint64 BigInteger::__normalizeNumbers(BigInteger& a, BigInteger& b, uint64 base) {
    uint64 normalization = 1;
    uint64 firstWordCopy = b.parts[b.parts.size() - 1];

    while (firstWordCopy < (base >> 1)) {
        firstWordCopy <<= 1;
        normalization <<= 1;
    }

    a *= normalization;
    b *= normalization;

    return normalization;
}

BigInteger BigInteger::__add(const BigInteger& lhs, const BigInteger& rhs) {
    // Doesn't take sign into account

    uint64 maxSize = max(lhs.parts.size(), rhs.parts.size());
    BigInteger out;
    out.parts.resize(maxSize);

    uint64 carryOver = 0;
    for (uint64 i = 0; i < maxSize; ++i) {
        out.parts[i] = (lhs.parts.size() > i ? lhs.parts[i] : 0) + (rhs.parts.size() > i ? rhs.parts[i] : 0) + carryOver;
        if (out.parts[i] >= WORD_VALUE_CAP) {
            out.parts[i] -= WORD_VALUE_CAP;
            carryOver = 1;
        } else {
            carryOver = 0;
        }
    }

    if (carryOver == 1) {
        out.parts.push_back(1);
    }

    return out;
}

BigInteger BigInteger::__subtract(const BigInteger& lhs, const BigInteger& rhs) {
    // Only for lhs >= rhs
    // Doesn't take sign into account

    uint64 maxSize = max(lhs.parts.size(), rhs.parts.size());

    BigInteger out;
    out.parts.resize(maxSize);

    uint64 borrow = 0;
    for (int64 i = 0; i < maxSize; ++i) {
        out.parts[i] = lhs.parts[i] + WORD_VALUE_CAP - (rhs.parts.size() > i ? rhs.parts[i] : 0) - borrow;
        if (out.parts[i] >= WORD_VALUE_CAP) {
            out.parts[i] -= WORD_VALUE_CAP;
            borrow = 0;
        } else {
            borrow = 1;
        }
    }

    while (out.parts.size() > 1 && out.parts[out.parts.size() - 1] == 0) {
        out.parts.pop_back();
    }

    return out;
}

BigInteger operator+(const BigInteger & lhs, const BigInteger & rhs) {
    BigInteger res;

    if (BigInteger::__greaterThanOrEqualAbs(lhs, rhs)) {
        if (lhs.sign && rhs.sign) {
            res = BigInteger::__add(lhs, rhs);
            res.sign = true;
        } else if (!lhs.sign && !rhs.sign) {
            res = BigInteger::__add(lhs, rhs);
            res.sign = false;
        } else if (lhs.sign && !rhs.sign) {
            res = BigInteger::__subtract(lhs, rhs);
            res.sign = (res.isZero() ? false : true);
        } else {
            res = BigInteger::__subtract(lhs, rhs);
            res.sign = false;
        }
    } else {
        if (lhs.sign && rhs.sign) {
            res = BigInteger::__add(lhs, rhs);
            res.sign = true;
        } else if (!lhs.sign && !rhs.sign) {
            res = BigInteger::__add(lhs, rhs);
            res.sign = false;
        } else if (lhs.sign && !rhs.sign) {
            res = BigInteger::__subtract(rhs, lhs);
            res.sign = false;
        } else {
            res = BigInteger::__subtract(rhs, lhs);
            res.sign = (res.isZero() ? false : true);
        }
    }

    return res;
}

BigInteger operator-(const BigInteger & lhs, const BigInteger & rhs) {
    BigInteger res;

    if (BigInteger::__greaterThanOrEqualAbs(lhs, rhs)) {
        if (lhs.sign && rhs.sign) {
            res = BigInteger::__subtract(lhs, rhs);
            res.sign = true;
        } else if (!lhs.sign && !rhs.sign) {
            res = BigInteger::__subtract(lhs, rhs);
            res.sign = false;
        } else if (lhs.sign && !rhs.sign) {
            res = BigInteger::__add(lhs, rhs);
            res.sign = true;
        } else {
            res = BigInteger::__add(lhs, rhs);
            res.sign = false;
        }
    } else {
        if (lhs.sign && rhs.sign) {
            res = BigInteger::__subtract(rhs, lhs);
            res.sign = false;
        } else if (!lhs.sign && !rhs.sign) {
            res = BigInteger::__subtract(rhs, lhs);
            res.sign = true;
        } else if (lhs.sign && !rhs.sign) {
            res = BigInteger::__add(lhs, rhs);
            res.sign = true;
        } else {
            res = BigInteger::__add(lhs, rhs);
            res.sign = false;
        }
    }

    return res;
}

BigInteger BigInteger::karatsubaMultiply(const BigInteger& x, const BigInteger& y) const {
    if (x.isZero() || y.isZero()) {
        return BigInteger();
    }

    if (x.parts.size() == 1 && y.parts.size() == 1) {
        BigInteger out;
        out.parts[0] = x.parts[0] * y.parts[0];
        if (out.parts[0] >= WORD_VALUE_CAP) {
            // Split into two chunks
            out.parts.push_back(out.parts[0] / WORD_VALUE_CAP);
            out.parts[0] %= WORD_VALUE_CAP;
        }
        return out;
    } else {
        uint64 offset = max(x.parts.size() >> 1, y.parts.size() >> 1);
        uint64 xoffset = (x.parts.size() < offset ? x.parts.size() : offset);
        uint64 yoffset = (y.parts.size() < offset ? y.parts.size() : offset);

        BigInteger x1(x.parts.begin() + xoffset, x.parts.end());
        BigInteger x2(x.parts.begin(), x.parts.begin() + xoffset);
        BigInteger y1(y.parts.begin() + yoffset, y.parts.end());
        BigInteger y2(y.parts.begin(), y.parts.begin() + yoffset);

        BigInteger z1(karatsubaMultiply(x1, y1));
        BigInteger z2(karatsubaMultiply(x2, y2));
        BigInteger z3(karatsubaMultiply(x1 + x2, y1 + y2) - z1 - z2);

        z1.shift(offset << 1);
        z3.shift(offset);

        return z1 + z2 + z3;
    }
}

BigInteger operator * (const BigInteger& x, const BigInteger& y) {
    BigInteger res(x.karatsubaMultiply(x, y));
    res.sign = x.sign ^ y.sign;
    return res;
}

BigInteger& BigInteger::operator *= (const uint64& y) {
    if (y == 0) {
        parts.resize(1);
        parts[0] = 0;
    } else {
        uint64 carry = 0;
        for (int64 i = 0; i < parts.size(); ++i) {
            parts[i] = parts[i] * y + carry;
            carry = parts[i] / WORD_VALUE_CAP;
            parts[i] %= WORD_VALUE_CAP;
        }

        if (carry) {
            parts.push_back(carry);
        }
    }

    return *this;
}

BigInteger& BigInteger::operator /= (const uint64& y) {
    uint64 remainder = 0;

    for (int64 i = parts.size() - 1; i >= 0; --i) {
        remainder = remainder * WORD_VALUE_CAP + parts[i];
        parts[i] = remainder / y;
        remainder %= y;
    }

    while (parts[parts.size() - 1] == 0 && parts.size() > 1) {
        parts.pop_back();
    }

    return *this;
}

BigInteger operator / (const BigInteger& lhs, const BigInteger& rhs) {
    return divideWithRemainder(lhs, rhs).quotient;
}

BigInteger operator % (const BigInteger& lhs, const BigInteger& rhs) {
    return divideWithRemainder(lhs, rhs).remainder;
}

IntegerDivisionResult divideWithRemainder(BigInteger lhs, BigInteger rhs) {
    uint64 normalization = BigInteger::__normalizeNumbers(lhs, rhs, WORD_VALUE_CAP);
    
    BigInteger quotient;
    uint64 quotientSize = lhs.parts.size() - rhs.parts.size();
    quotient.parts.resize(quotientSize);
    quotient.sign = lhs.sign ^ rhs.sign;
    lhs.sign = false;
    rhs.sign = false;

    for (int64 j = quotientSize - 1; j >= 0; --j) {
        uint64 mx = (lhs.parts[rhs.parts.size() + j] * WORD_VALUE_CAP + lhs.parts[rhs.parts.size() + j - 1]) / rhs.parts[rhs.parts.size() - 1];
        quotient.parts[j] = min(WORD_VALUE_CAP - 1, mx);
        BigInteger shiftedDisivor(rhs.copyShift(j));
        lhs = lhs - quotient.parts[j] * shiftedDisivor;
        while (lhs < 0) {
            --quotient.parts[j];
            lhs = lhs + shiftedDisivor;
        }
    }

    lhs /= normalization;
    return IntegerDivisionResult(quotient, lhs);
}

bool BigInteger::__greaterThanOrEqualAbs(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.parts.size() > rhs.parts.size()) {
        return true;
    }

    if (lhs.parts.size() < rhs.parts.size()) {
        return false;
    }

    for (int64 i = lhs.parts.size() - 1; i >= 0; --i) {
        if (lhs.parts[i] > rhs.parts[i]) {
            return true;
        } else if (lhs.parts[i] < rhs.parts[i]) {
            return false;
        }
    }

    return true; // lhs is equal to rhs
}

bool operator == (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.parts.size() != rhs.parts.size() || rhs.sign != lhs.sign) {
        return false;
    }

    for (int64 i = 0; i < lhs.parts.size(); ++i) {
        if (lhs.parts[i] != rhs.parts[i]) {
            return false;
        }
    }

    return true;
}

bool operator < (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.parts.size() < rhs.parts.size() || (lhs.sign && !rhs.sign)) {
        return true;
    }

    if (lhs.parts.size() > rhs.parts.size() || (!lhs.sign && rhs.sign)) {
        return false;
    }

    for (int64 i = lhs.parts.size() - 1; i >= 0; --i) {
        if (lhs.parts[i] > rhs.parts[i]) {
            return false;
        } else if (lhs.parts[i] < rhs.parts[i]) {
            return true;
        }
    }

    return false; // lhs is equal
}

bool operator > (const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.parts.size() > rhs.parts.size() || (!lhs.sign && rhs.sign)) {
        return true;
    }

    if (lhs.parts.size() < rhs.parts.size() || (lhs.sign && !rhs.sign)) {
        return false;
    }

    for (int64 i = lhs.parts.size() - 1; i >= 0; --i) {
        if (lhs.parts[i] > rhs.parts[i]) {
            return true;
        } else if (lhs.parts[i] < rhs.parts[i]) {
            return false;
        }
    }

    return false; // lhs is equal
}

bool _iswhitespace(char a) {
    return a <= 32;
}

std::istream& operator >> (std::istream& stream, BigInteger& number) {
    while (_iswhitespace(stream.peek())) {
        stream.get();
    }

    std::string stringNumber;
    stream >> stringNumber;
    uint64 word = 0;
    for (int64 i = stringNumber.size() - 1; i >= 0; i -= MAX_DIGITS, word = 0) {
        for (int64 j = (i - static_cast<int64>(MAX_DIGITS) + 1 >= 0 ? i - MAX_DIGITS + 1 : 0); j <= i; ++j) {
            word *= 10;
            word += stringNumber[j] - 48;
        }
        number.parts.push_back(word);
    }

    return stream;
}

std::ostream& operator << (std::ostream& stream, const BigInteger& number) {
    stream << number.parts[number.parts.size() - 1];
    stream << std::setfill('0') << std::setw(MAX_DIGITS); // Set stream formatting to pad with additional zeros up to MAX_DIGITS
    for (int64 i = static_cast<int64>(number.parts.size()) - 2; i >= 0; --i) {
        stream << number.parts[i];
    }
    stream << std::setfill(' ') << std::setw(0); // Reset stream formatting
    return stream;
}