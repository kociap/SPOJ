#include "BigNumber.h"

constexpr int digitsPerPart = 19;
constexpr uint64 carry = 10000000000000000000ULL;

bool _isWhiteSpace(const char& c) {
    return c <= 32;
}

void getDigitsFromInput(std::istream& io, BigNumber& number, const uint32& digitCount, const char& delimiter) {
    number.parts.resize(0); // Remove all old parts
    while (_isWhiteSpace(io.peek())) { // Skip leading whitespaces
        io.get();
    }

    char* input = new char[digitCount];
    io.get(input, digitCount, delimiter);
    io.clear(); // Ensure all future io operations are ok

    for (int i = io.gcount() - 1; i >= 0; i -= digitsPerPart) {
        uint64 a = 0;
        for (int j = (i >= digitsPerPart ? i - digitsPerPart + 1 : 0); j <= i; ++j) {
            a *= 10;
            a += input[j] - 48;
        }
        number.parts.push_front(a);
    }

    delete input;
}


int64 mod(const BigNumber& number, const uint32& x) {
    uint64 result = number.parts[0] % x;
    for (size_t i = 1; i < number.parts.size(); ++i) {
        result = ((result * (carry % x)) % x + number.parts[i] % x) % x;
    }
    return static_cast<uint32>(result);
}

bool operator>(const BigNumber& lhs, const uint32& rhs) {
    if (lhs.parts.size() > 1) {
        return true;
    } else {
        return lhs.parts[0] > rhs;
    }
}

uint32 BigNumber::toUInt32() {
    if (parts.size() > 0) {
        return static_cast<uint32>(parts[parts.size() - 1]);
    } else {
        return 0;
    }
}