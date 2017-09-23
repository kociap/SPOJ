#ifndef MATHEXTENDED_H
#define MATHEXTENDED_H
#include <vector>

using uint64 = unsigned long long;
using uint32 = unsigned int;
using int64 = long long;
using int32 = int;

struct PrimeFactor {
    uint32 prime;
    uint32 primeCount;
    uint32 factor; // prime ^ primeCount

    PrimeFactor(const uint32& _prime, const uint32& _primeCount, const uint32& _factor);
    PrimeFactor(const uint32& _prime, const uint32& _primeCount);
};

int64 eulersTotient(PrimeFactor n);
int64 eulersTotient(uint32 n);
int64 exponentiateBySquaring(uint32 base, uint32 exponent, const uint32& modulus);
int64 modularInverse(uint32 number, uint32 modulus);
std::vector<PrimeFactor> factorizePrime(uint32 n);
int64 gcd(uint32 a, uint32 b);
void eratosthenesSieve(uint32 upperBound, std::vector<uint32> & out);
#endif // !MATHEXTENDED_H
