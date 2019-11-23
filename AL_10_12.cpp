#include <iostream>
using namespace std;

inline long long gcd(long long a, long long b);


long long a, b, c, lcmAB, lcmAC, lcmBC, lcmABC;

int main() {
	ios::sync_with_stdio(false);
	cin >> a >> b >> c;

	lcmAB = a / gcd(a, b) * b;
	lcmAC = a / gcd(a, c) * c;
	lcmBC = b / gcd(b, c) * c;
	lcmABC = lcmAB / gcd(lcmAB, c) * c;

	long long x, y;

	while (cin >> x >> y) {

		x--;

		long long sum = (y / a - x / a) + (y / b - x / b) + (y / c - x / c) + (y / lcmABC - x / lcmABC) - (y / lcmAB - x / lcmAB) - (y / lcmBC - x / lcmBC) - (y / lcmAC - x / lcmAC);


		cout << sum << endl;
	}

	return 0;
}

inline long long gcd(long long a, long long b) {
	long long c;
	while (b) {
		c = a % b;
		a = b;
		b = c;

	}
	return a;
}
