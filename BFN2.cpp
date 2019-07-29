#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

using uint32 = unsigned int;

inline void eratoshtenesSieve(vector<uint32>& primes, const uint32 maxPrime);
inline void sieveSegment(const vector<uint32>& precomputedPrimes, const uint32 begin, const uint32 end);

int main() {
    ios::sync_with_stdio(false);

    const uint32 MAX_PRIME_SQRT = 46341;

    vector<uint32> primes;

    eratoshtenesSieve(primes, MAX_PRIME_SQRT);

    uint32 t;
    cin >> t;
    
    while (t--) {
        uint32 u, l;
        cin >> u >> l;

        if (u < MAX_PRIME_SQRT) {
            for (uint32 prime : primes) {
                if (prime >= u && prime <= l) {
                    cout << prime << "\n";
                }
            }

            if (l >= MAX_PRIME_SQRT) {
                sieveSegment(primes, MAX_PRIME_SQRT, l);
            }
        } else {
            sieveSegment(primes, u, l);
        }
    }

    return 0;
}

inline void eratoshtenesSieve(vector<uint32>& primes, const uint32 maxPrime) {
    uint32 maxPrimeSqrt = static_cast<uint32>(sqrt(maxPrime));
    vector<char> isPrime(maxPrime + 1, true);

    for (uint32 i = 3; i <= maxPrimeSqrt; i += 2) {
        if (isPrime[i]) {
            for (uint32 j = i * i; j <= maxPrime; j += i << 1) {
                isPrime[j] = false;
            }
        }
    }

    primes.push_back(2);
    for (uint32 i = 3; i <= maxPrime; i += 2) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
}

inline void sieveSegment(const vector<uint32>& precomputedPrimes, const uint32 begin, const uint32 end) {
    uint32 segmentSize = end - begin + 1;

    // Sieved segment
    vector<char> segment(segmentSize, true);

    // Index of first occurences of a primes' multiples in the given interval
    vector<uint32> firstOccurence(precomputedPrimes.size(), 0);

    // Calculate first occurence of each prime
    for (uint32 i = 0; i < precomputedPrimes.size(); ++i) {
        firstOccurence[i] = (begin / precomputedPrimes[i]) * precomputedPrimes[i];

        if (firstOccurence[i] < begin) {
            firstOccurence[i] += precomputedPrimes[i];
        }

        // Make sure to skip even multiples
        if ((firstOccurence[i] & 1) == 0) {
            firstOccurence[i] += precomputedPrimes[i];
        }
    }

    // Sieve segment
    for (uint32 i = 1; i < firstOccurence.size(); ++i) {
        uint32 ithPrimeMultiple = firstOccurence[i];

        while (ithPrimeMultiple <= end) {
            segment[ithPrimeMultiple - begin] = false;
            ithPrimeMultiple += precomputedPrimes[i] << 1;
        }
    }

    // Print the segment
    for (uint32 i = ((begin & 1) == 1 ? 0 : 1); i < segmentSize; i += 2) {
        if (segment[i]) {
            cout << i + begin << "\n";
        }
    }
}
