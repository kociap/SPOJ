#include <iostream>
#include <cmath>

using namespace std;

int main() {
	ios::sync_with_stdio(false);

	double n;
	while (cin >> n) {
		cout << static_cast<long long>(ceil(sqrt(2.0 * (n - 1.0) + 0.25) - 0.5)) << endl;
	}

	return 0;
}