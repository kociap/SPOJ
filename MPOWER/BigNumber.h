#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include <istream>
#include <deque>

using uint32 = unsigned int;
using uint64 = unsigned long long;
using int64 = long long;

class BigNumber;

int64 mod(const BigNumber& number, const uint32& modulus);
bool operator>(const BigNumber& lhs, const uint32& rhs);

class BigNumber {
	friend void getDigitsFromInput(std::istream& io, BigNumber& number, const uint32& digitCount, const char& delimiter);
	friend int64 mod(const BigNumber& number, const uint32& modulus);
	friend bool operator>(const BigNumber& lhs, const uint32& rhs);

private:
	std::deque<uint64> parts;

public:
	BigNumber(): parts(1, 0) {}
	BigNumber(const uint32& number): parts(1, number) {}
#ifdef _MPOWER_DEBUG
	BigNumber(const std::deque<uint64>& vec): parts(vec) {}
#endif // _MPOWER_DEBUG
	uint32 toUInt32();
};
#endif // !BIGNUMBER_H
