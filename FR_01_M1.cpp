#include <cstdio>

using namespace std;

inline unsigned long long quickPower(unsigned long long base, int exponent);

int main() {

	int t;
	scanf("%d", &t);

	while (t--) {
		unsigned long long n;
		int k;
		scanf("%d %llu", &k, &n);
		if (k == 1) {
			printf("%llu\n", n);
		} else {
			printf("%llu\n", (n - 1) * quickPower(n, k - 1));
		}
	}

	return 0;
}

inline unsigned long long quickPower(unsigned long long base, int exponent) {
	if (exponent == 0) {
		return 1ULL;
	} else if (exponent == 1) {
		return base;
	} else {
		if ((exponent & 1) == 1) {
			unsigned long long number = quickPower(base, exponent >> 1);
			return number * number * base;
		} else {
			unsigned long long number = quickPower(base, exponent >> 1);
			return number * number;
		}
	}
}