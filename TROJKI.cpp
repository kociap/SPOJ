#include <iostream>
#include <set>
using namespace std;

struct PythagoreanTriple {
	int a;
	int b;
	int c;

	PythagoreanTriple(): a(0), b(0), c(0) {}
	PythagoreanTriple(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
};

int gcd(int a, int b);
bool isSmaller(const PythagoreanTriple &, const PythagoreanTriple &);

int main() {
	ios::sync_with_stdio(false);

	set<PythagoreanTriple, decltype(isSmaller)*>triples(isSmaller);
	int x;
	int a, b, c;
	cin >> x;

	for (int n = 2; n * n + 1 <= x; ++n) {
		for (int m = 1; m < n; ++m) {
			a = n * n - m * m;
			b = 2 * m * n;
			c = m * m + n * n;
			if (c > x) {
				break;
			}
			for (int k = 1; c * k <= x; ++k) {
				if (a < b) {
					triples.emplace(PythagoreanTriple(a * k, b * k, c * k));
				} else {
					triples.emplace(PythagoreanTriple(b * k, a * k, c * k));
				}
			}
		}
	}

	for (set<PythagoreanTriple>::const_iterator i = triples.cbegin(); i != triples.cend(); ++i) {
		cout << i->a << " " << i->b << " " << i->c << endl;
	}

	return 0;
}

bool isSmaller(const PythagoreanTriple & lhs, const PythagoreanTriple & rhs) {
	if (lhs.a < rhs.a) return true;
	if (lhs.a == rhs.a) {
		if (lhs.b < rhs.b) return true;
		if (lhs.b == rhs.b) {
			return lhs.c < rhs.c;
		}
	}
	return false;
}

int gcd(int a, int b) {
	int c;
	while (b) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

