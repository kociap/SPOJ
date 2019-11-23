#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

inline const double square(const double & base) {
	return base * base;
}

inline const double cube(const double & base) {
	return base * base * base;
}

inline const double areaUnderParabola(const double & a, const double & b, const double & c, const double & x1, const double & x2) {
	return (a / 3 * cube(x1) + b / 2 * square(x1) + c * x1 - a / 3 * cube(x2) - b / 2 * square(x2) - c * x2);
}

inline const double absoluteValue(const double & value) {
	if (value <= 0) {
		return -value;
	} else {
		return value;
	}
}

int main() {
	ios::sync_with_stdio();

	int t;
	cin >> t;
	while (t--) {
		// a, b, c - first parabola coefficients; d, e, f - second parabola coefficients;
		double a, b, c, d, e, f;
		cin >> a >> b >> c >> d >> e >> f;

		double delta = square(b - e) - 4 * (a - d) * (c - f);
		if (delta <= 0) {
			cout << "0.00" << endl;
			continue;
		}

		double deltaSqrt = sqrt(square(b - e) - 4 * (a - d) * (c - f));
		// parabolas' intersection points
		double x1 = (e - b - deltaSqrt) / (2 * (a - d)), x2 = (e - b + deltaSqrt) / (2 * (a - d));
		cout << fixed << setprecision(2) << absoluteValue(areaUnderParabola(a, b, c, x1, x2) - areaUnderParabola(d, e, f, x1, x2)) << endl;
	}

	return 0;
}