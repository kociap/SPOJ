#include <stdio.h>

#define INPUT_BUFFER_SIZE 262143

using i64 = long long;
using i32 = int;
using u8 = unsigned char;

struct String_View {
    char* begin;
    char* end;
};

struct Input_Buffer {
    char buf[INPUT_BUFFER_SIZE + 1];
    char* i;
    char* end;

    Input_Buffer(): i(buf), end(buf) {
        buf[INPUT_BUFFER_SIZE] = EOF;
    }

    bool read_i64(i64& v) {
        if(end - i < 30) {
            i64 remaining = end - i;
            char* b = i;
            i = buf;
            while(b != end) {
                *i = *b;
                ++i;
                ++b;
            }

            i64 count = fread(i, 1, INPUT_BUFFER_SIZE - remaining, stdin);
            i = buf;
            end = buf + remaining + count;
            *end = EOF;
        }

        while((*i > '9' | *i < '0') & *i != EOF) {
            ++i;
        }

        if(i == end) {
            return false;
        }
        
        v = 0;
        while(*i >= '0' & *i <= '9') {
            v *= 10;
            v += *i - '0';
            ++i;
        }

        return true;
    }
};

struct Output_Buffer {
public:
    char buf[65536];
    char* i;
    char* end;

    Output_Buffer(): i(buf), end(buf + 65536) {}

    ~Output_Buffer() {
        fwrite(buf, 1, i - buf, stdout);
    }

    void write_i64(i64 v) {
        if(end - i < 30) {
            fwrite(buf, 1, i - buf, stdout);
            i = buf;
        }

        char buffer[21];
        String_View number = to_string(v, buffer);
        for(; number.begin != number.end; ++number.begin, ++i) {
            *i = *number.begin;
        }
    }

    void write_newline() {
        if(end - i < 1) {
            fwrite(buf, 1, i - buf, stdout);
            i = buf;
        }

        *i = '\n';
        ++i;
    }

private:
    // buffer must be a char array of 21 elements.
    String_View to_string(i64 v, char* buffer) {
        // We don't need null-terminator or initialized elements.
        bool has_sign = false;
        if(v < 0) {
            has_sign = true;
            v = -v;
        }

        i32 i = 20;
        do {
            buffer[i] = (v % 10) | '0';
            --i;
            v /= 10;
        } while(v > 0);
        buffer[i] = '-';
        return {buffer + i + !has_sign, buffer + 21};
    }
};

struct Ternary_i64 {
private:
    char control = 1;
    char bits[41];

public:
    Ternary_i64(i64 v) {
        for(i64 i = 0; i < 41; ++i) {
            bits[i] = v % 3;
            v /= 3;
        }
    }

    void ternary_xor(Ternary_i64 const& rhs) {
        control = (control + rhs.control) % 3;
        for(i64 i = 0; i < 41; ++i) {
            bits[i] = (bits[i] + rhs.bits[i]) % 3;
        }
    }

    i64 to_i64() {
        i64 v = 0;
        if(control == 2) {
            for(i64 i = 40; i > -1; --i) {
                v *= 3;
                v += bits[i];
            }
        } else {
            for(i64 i = 40; i > -1; --i) {
                v *= 3;
                v += (bits[i] + bits[i]) % 3;
            }
        }
        return v;
    }
};

int main() {
    // setvbuf(stdin, nullptr, _IONBF, INPUT_BUFFER_SIZE + 1);
    Input_Buffer in;
    Output_Buffer out;

    Ternary_i64 value(0);
    i64 a;
    while(in.read_i64(a)) {
        value.ternary_xor(a);
    }

    out.write_i64(value.to_i64());

    return 0;
}
