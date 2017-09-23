#include "MathExtended.h"
#include <math.h>

PrimeFactor::PrimeFactor(const uint32& _prime, const uint32& _primeCount, const uint32& _factor): prime(_prime), primeCount(_primeCount), factor(_factor) {}
PrimeFactor::PrimeFactor(const uint32& _prime, const uint32& _primeCount): prime(_prime), primeCount(_primeCount), factor(pow(_prime, _primeCount)) {}

std::vector<uint32> primes{ 2, 3, 5, 7, 11, 13, 17, 19 };

int64 eulersTotient(PrimeFactor n) {
    return n.factor / n.prime * (n.prime - 1);
}

int64 eulersTotient(uint32 n) {
    auto primeFactorization = factorizePrime(n);
    int64 result = 1;
    for (const PrimeFactor& primeFactor : primeFactorization) {
        result *= static_cast<int64>(pow(primeFactor.prime, primeFactor.primeCount - 1)) * (primeFactor.prime - 1);
    }

    return result;
}

uint64 _exponentiateBySquaring(uint32 base, uint32 exponent, const uint32& modulus) {
    if (exponent == 0) {
        return 1;
    }

    if (exponent == 1) {
        return base;
    }

    if ((exponent & 1) == 1) {
        auto expResult = _exponentiateBySquaring(base, exponent >> 1, modulus);
        return (base * expResult) % modulus * expResult % modulus;
    } else {
        auto expResult = _exponentiateBySquaring(base, exponent >> 1, modulus);
        return expResult * expResult % modulus;
    }
}

int64 exponentiateBySquaring(uint32 base, uint32 exponent, const uint32& modulus) {
    return static_cast<uint32>(_exponentiateBySquaring(base % modulus, exponent, modulus));
}

int64 modularInverse(uint32 number, uint32 modulus) {
    uint32 modulusCopy = modulus;
    int64 inverse = 0;
    int64 inverseCarry = 1;
    int64 gcdSwap, inverseSwap;
    int64 quotient;
    while (number != 0) {
        quotient = modulus / number;
        // gcd
        gcdSwap = modulus;
        modulus = number;
        number = gcdSwap - quotient * number;
        // inverse
        inverseSwap = inverse;
        inverse = inverseCarry;
        inverseCarry = inverseSwap - quotient * inverseCarry;
    }

    return inverse < 0 ? inverse + modulusCopy : inverse;
}

std::vector<PrimeFactor> factorizePrime(uint32 n) {
    std::vector<PrimeFactor> primeFactors;
    // n + 2 for n = 2
    for (size_t i = 0; i < primes.size() && ((n + 2) >> 1) >= primes[i]; ++i) {
        if (n % primes[i] == 0) {
            uint32 count = 1;
            n /= primes[i];
            while (n % primes[i] == 0) {
                ++count;
                n /= primes[i];
            }
            primeFactors.emplace_back(primes[i], count);
        }
    }
    primeFactors.emplace_back(n, 1);
    return primeFactors;
}

int64 gcd(uint32 a, uint32 b) {
    uint32 c;
    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

void eratosthenesSieve(uint32 upperBound, std::vector<uint32> & out) {
    uint32 upperBoundSqrt = sqrt(upperBound);
    std::vector<bool> isPrime(upperBound + 1, true);

    for (uint32 i = 3; i <= upperBoundSqrt; i += 2) {
        if (isPrime[i]) {
            for (uint32 j = i * i; j <= upperBound; j += i << 1) {
                isPrime[j] = false;
            }
        }
    }

    out.emplace_back(2);
    for (uint32 i = 3; i <= upperBound; i += 2) {
        if (isPrime[i]) {
            out.emplace_back(i);
            if (i > primes.back()) {
                primes.emplace_back(i);
            }
        }
    }
}