#include <stdio.h>

using i64 = long long;
using u8 = unsigned char;

struct Input_Buffer {
    char buf[65536];
    char* i;
    char* end;

    Input_Buffer(): i(buf), end(buf) {
        buf[65535] = EOF;
    }

    i64 read_i64() {
        if(end - i < 10) {
            i64 remaining = end - i;
            char* b = i;
            i = buf;
            while(b != end) {
                *i = *b;
                ++i;
                ++b;
            }

            i64 count = fread(i, 1, 65535 - remaining, stdin);
            i = buf;
            end = buf + remaining + count;
        }

        while(*i > '9' | *i < '0') {
            ++i;
        }

        i64 v = 0;
        while(*i >= '0' & *i <= '9') {
            v *= 10;
            v += *i - '0';
            ++i;
        }

        return v;
    }
};

struct Output_Buffer {
    char buf[65536];
    char* i;
    char* end;

    Output_Buffer(): i(buf), end(buf + 65536) {}

    ~Output_Buffer() {
        fwrite(buf, 1, i - buf, stdout);
    }

    void write_i64(i64 v) {
        if(end - i < 3) {
            fwrite(buf, 1, i - buf, stdout);
            i = buf;
        }

        bool offset = v >= 10;
        i[0] = '1';
        i[0 + offset] = v % 10 + '0';
        i[1 + offset] = '\n';
        i += 2 + offset;
    }
};

int main() {
    // setvbuf(stdin, nullptr, _IONBF, 1);
    // setvbuf(stdout, nullptr, _IONBF, 1);
    Input_Buffer inbuf;
    Output_Buffer outbuf;
    i64 t = inbuf.read_i64();
    u8 ter_buf[32] = {};

    for(; t > 0; --t) {
        i64 n = inbuf.read_i64();
        i64 i = 0;
        i64 ones = 0;
        i64 two_pos = -1;
        for(; n > 0; i += 4) {
            ter_buf[i] = n % 3;
            ter_buf[i + 1] = (n / 3) % 3;
            ter_buf[i + 2] = (n / 9) % 3;
            ter_buf[i + 3] = (n / 27) % 3;
            n /= 81;

            if(ter_buf[i] == 2) {
                two_pos = i;
                ones = 0;
            } else {
                ones += ter_buf[i];
            }

            if(ter_buf[i + 1] == 2) {
                two_pos = i + 1;
                ones = 0;
            } else {
                ones += ter_buf[i + 1];
            }

            if(ter_buf[i + 2] == 2) {
                two_pos = i + 2;
                ones = 0;
            } else {
                ones += ter_buf[i + 2];
            }

            if(ter_buf[i + 3] == 2) {
                two_pos = i + 3;
                ones = 0;
            } else {
                ones += ter_buf[i + 3];
            }
        }

        i64 c = ones + two_pos + 1;
        outbuf.write_i64(c);
    }

    return 0;
}
