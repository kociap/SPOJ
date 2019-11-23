#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
	long long x;
	long long y;
	Point(): x(0), y(0) {}
	Point(long long _x, long long _y): x(_x), y(_y) {}
};

inline bool areCollinear(Point a, Point b, Point c) {
	long long determinanat = a.x * b.y - a.y * b.x + b.x * c.y - c.y * a.x + c.x * a.y - b.y * c.x;
	return determinanat == 0;
}

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		if (n < 3) {
			for (int i = 0; i < n; ++i) {
				long long a;
				cin >> a >> a;
			}
			cout << "TAK" << endl;
			continue;
		}

		vector<Point> points;
		for (int i = 0; i < n; ++i) {
			long long x, y;
			cin >> x >> y;
			points.emplace_back(x, y);
		}

		sort(points.begin(), points.end(), [](Point a, Point b) -> bool { return a.x < b.x && a.y < b.y; });
		points.erase(unique(points.begin(), points.end(), [](Point a, Point b) -> bool { return a.x == b.x && a.y == b.y; }), points.end());

		bool areAllCollinear = true;
		for (int i = 0; i + 2 < points.size(); ++i) {
			if (!areCollinear(points[i], points[i + 1], points[i + 2])) {
				cout << "NIE" << endl;
				areAllCollinear = false;
				break;
			}
		}

		if (areAllCollinear) {
			cout << "TAK" << endl;
		}
	}

	return 0;
}

