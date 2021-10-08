#include <iostream>
#include <array>
#include <vector>

using i64 = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    i64 t = 0;
    std::cin >> t;
    std::array<i64, 19> powers = {387420489, 129140163, 43046721, 14348907, 4782969, 1594323, 531441, 177147, 59049, 19683, 6561, 2187, 729, 243, 81, 27, 9, 3, 1};
    std::vector<i64> numbers(t, 0);
    std::vector<i64> counts(t, 0);
    for(i64* i = numbers.data(), *end = numbers.data() + t; i != end; ++i) {
        std::cin >> *i;
    }

    for(i64 p: powers) {
        i64* n = numbers.data();
        i64* n_end = numbers.data() + t;
        i64* c = counts.data();
        i64* c_end = counts.data() + t;
        for(; n != n_end; ++n, ++c) {
            // if(*n >= p) {
            //     *n -= p;
            //     *c += 1;
            // }
            bool g = *n >= p;
            *n -= p * g;
            *c += g;
        }
    }
    
    for(i64 c: counts) {
        std::cout << c << '\n';
    }

    return 0;
}
