#define _MPOWER_DEBUG
#undef _MPOWER_DEBUG
#include <iostream>
#include "BigNumber.h"
#include "MathExtended.h"

int main() {
    using namespace std;

    ios::sync_with_stdio(false);
#ifdef _MPOWER_DEBUG
    std::deque<uint64> vec{ 4790191284987252, 3461864631327232122 };
    auto md = mod(vec, 276);
#endif // _MPOWER_DEBUG

    vector<uint32> primes;
    eratosthenesSieve(65536, primes);

    int t;
    cin >> t;
    while (t--) {
        uint32 base, modulus;
        BigNumber exponent;

        cin >> base;
        getDigitsFromInput(cin, exponent, 10002, ' ');
        cin >> modulus;

        if (base == modulus) {
            cout << 0 << endl;
            continue;
        }

        auto exponentiateUsingTotient = [](const uint32& base, const BigNumber& exponent, const uint32& modulus) -> uint32 {
            auto totient = eulersTotient(modulus);
            auto reducedExponent = mod(exponent, totient);
            return exponentiateBySquaring(base, reducedExponent, modulus);
        };

        if (gcd(base, modulus) == 1) {
            // base and modulus are coprime
            cout << exponentiateUsingTotient(base, exponent, modulus) << endl;
        } else {
            struct ModuloResult {
                uint32 modulus;
                uint32 result;

                ModuloResult(uint32 _result, uint32 _modulus): result(_result), modulus(_modulus) {}
            };

            vector<PrimeFactor> primeFactors = factorizePrime(modulus);
            vector<ModuloResult> moduloResults;

            // Calculate modulo resutls for powers of prime numbers
            for (const auto& primeFactor : primeFactors) {
                if (gcd(base, primeFactor.factor) > 1) {
                    if (exponent > primeFactor.primeCount) {
                        // Anything that is of form
                        //     a * b^x mod b^y
                        //   where x >= y is congruent to 0
                        moduloResults.emplace_back(0, primeFactor.factor);
                    } else {
                        // Converting exponent to uint32 is legal because exponent is smaller than primeCount
                        //   which is in general small (at most 31)
                        moduloResults.emplace_back(exponentiateBySquaring(base, exponent.toUInt32(), primeFactor.factor), primeFactor.factor);
                    }
                } else {
                    auto totient = eulersTotient(primeFactor);
                    auto reducedExponent = mod(exponent, totient);
                    moduloResults.emplace_back(exponentiateBySquaring(base, reducedExponent, primeFactor.factor), primeFactor.factor);
                }
            }

            uint64 result = 0;
            // Apply CRT
            for (const auto& moduloResult : moduloResults) {
                result += modulus / moduloResult.modulus * moduloResult.result * modularInverse(modulus / moduloResult.modulus, moduloResult.modulus);
            }

            cout << result % modulus << endl;
        }
    }

    return 0;
}
