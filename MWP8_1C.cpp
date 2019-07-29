#include <iostream>
#include <vector>
#include <cstdint>

class String {
public:
    char& operator[](uint32_t index) {
        return elements[index];
    }

    char operator[](uint32_t index) const {
        return elements[index];
    }

    uint32_t size() const {
        return _size;
    }

    void recalculate_size() {
        _size = 0;
        for(; elements[_size] != '\0'; ++_size); // strings are always null-terminated
    }


private:
    uint32_t _size = 0;
    char elements[21]; // 21 is the max palindrome length + null terminator

    friend String operator+(String const&, String const&);
    friend String concat_to_lower(String const&, String const&);
};

String concat_to_lower(String const& a, String const& b) {
    String c;
    int i = 0;
    for(; i < a.size(); ++i) {
        c[i] = tolower(a[i]);
    }
    for(; i - a.size() < b.size(); ++i) {
        c[i] = tolower(b[i - a.size()]);
    }
    c[i] = '\0';
    c._size = a._size + b._size;
    return c;
}

String operator+(String const& a, String const& b) {
    String c;
    int i = 0;
    for(; i < a.size(); ++i) {
        c[i] = a[i];
    }
    for(; i - a.size() < b.size(); ++i) {
        c[i] = b[i - a.size()];
    }
    c[i] = '\0';
    c._size = a._size + b._size;
    return c;
}

void get(String& a) {
    char c = std::cin.get();

    while((c == ' ' || c == '\n') && c != EOF) {
        c = std::cin.get();
    }

    int i = 0;
    while(c != ' ' && c != '\n' && c != EOF) {
        a[i++] = c;
        c = std::cin.get();
    }

    a[i] = '\0';
    a.recalculate_size();
}

void put(String const& a) {
    for(int i = 0; a[i] != '\0'; ++i) {
        std::cout.put(a[i]);
    }
}

bool isPalindrome(String const&, String const&);

int main() {
    std::ios::sync_with_stdio(false);

    std::vector<String> v, a;
    int t;

    std::cin >> t;
    while(t--) {
        String n;
        get(n);
        v.push_back(n);
    }

    std::cin >> t;
    while(t--) {
        String n;
        get(n);
        a.push_back(n);
    }

    int sz1 = v.size(), sz2 = a.size();
    bool a_first = false;
    int longest_palindrome_length = 0;
    int i_saved = 0;
    int j_saved = 0;
    for(int i = 0; i < sz1; ++i) {
        for(int j = 0; j < sz2; ++j) {
            if(v[i].size() + a[j].size() > longest_palindrome_length) {
                if(isPalindrome(v[i], a[j])) {
                    longest_palindrome_length = v[i].size() + a[j].size();
                    i_saved = i;
                    j_saved = j;
                    a_first = false;
                } else if(isPalindrome(a[j], v[i])) {
                    longest_palindrome_length = a[j].size() + v[i].size();
                    i_saved = i;
                    j_saved = j;
                    a_first = true;
                }
            }
            if(longest_palindrome_length == 20) break;
        }
    }

    std::cout << longest_palindrome_length << '\n';
    if(longest_palindrome_length != 0) {
        if(a_first) {
            put(a[j_saved] + v[i_saved]);
        } else {
            put(v[i_saved] + a[j_saved]);
        }
    }

    return 0;
}

bool isPalindrome(String const& a, String const& b) {
    String c = concat_to_lower(a, b);
    int i = 0;
    int j = c.size() - 1;
    while(i < j && c[i] == c[j]) {
        ++i;
        --j;
    }
    return i >= j;
}
