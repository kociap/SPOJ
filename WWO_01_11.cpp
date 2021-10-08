#include <stdio.h>
#include <iostream>
#include <array>
#include <vector>

using i64 = long long;

static i64 numbers[1000000] = {};
static i64 counts[1000000] = {};
static i64 const powers[19] = {387420489, 129140163, 43046721, 14348907, 4782969, 1594323, 531441, 177147, 59049, 19683, 6561, 2187, 729, 243, 81, 27, 9, 3, 1};

struct IO_Buffer {
    char buf[65536];
    std::basic_streambuf<char, std::char_traits<char>>* rdbuf;
    char* i;
    char* end;

    IO_Buffer(): rdbuf(std::cin.rdbuf()), i(buf), end(buf) {}

    char get() {
        if(i == end) {
            i64 count = rdbuf->sgetn(buf, 65536);
            i = buf;
            end = buf + count;
        }

        if(i == end) {
            return EOF;
        }

        char c = *i;
        ++i;
        return c;
    }

    i64 read_i64() {
        char c = get();
        while((c < '0' || c > '9') && c != EOF) {
            c = get();
        }

        if(c == EOF) {
            return -1;
        }

        i64 v = 0;
        while(c >= '0' && c <= '9') {
            v *= 10;
            v += c - '0';
            c = get();
        }

        return v;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    setvbuf(stdout, nullptr, _IOFBF, 65365);
    IO_Buffer io_buffer;
    i64 t = io_buffer.read_i64();
    i64* const c_b = counts;
    i64* const c_e = counts + t;
    i64* const n_b = numbers;
    i64* const n_e = numbers + t;
    for(i64* n = n_b, *end = n_e; n != end; ++n) {
        *n = io_buffer.read_i64();
    }

    for(i64 p: powers) {
        i64* n = n_b;
        i64* c = c_b;
        for(; n != n_e; ++n, ++c) {
            // if(*n >= p) {
            //     *n -= p;
            //     *c += 1;
            // }
            bool g = *n >= p;
            *n -= p * g;
            *c += g;
        }
    }
    
    char buf[4] = {'1', '0', '\0'};
    for(i64* c = c_b; c != c_e; ++c) {
        bool offset = *c < 10;
        buf[1] = *c % 10 + '0';
        puts(buf + offset);
    }

    return 0;
}
