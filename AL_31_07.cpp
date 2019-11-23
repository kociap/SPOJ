#include <iostream>

int main() {
	using namespace std;
	ios::sync_with_stdio(false);

	int fractalRecursionDepth;
	cin >> fractalRecursionDepth;

	int fractalSize = 1;
	for (int i = 1; i < fractalRecursionDepth; ++i) {
		fractalSize = fractalSize * 2 + 1;
	}

	auto getHighestDividingPowerOf2 = [](int number) -> int {
		for (int i = 0, out = 1; true; ++i, number >>= 1, out <<= 1) {
			if (((number >> 1) << 1) != number) {
				return out;
			}
		}
	};

	for (int row = 1; row <= fractalSize; ++row) {
		if ((row & 1) == 1) { // +|+|+|...
			for (int column = 1; column <= fractalSize; ++column) {
				if ((column & 1) == 1) {
					cout << '+';
				} else {
					cout << '|';
				}
			}
		} else {
			bool insertPipe = false;
			int numberOfDashes = getHighestDividingPowerOf2(row) - 1;
			for (int column = 1; column <= fractalSize;) {
				if ((column & 1) == 0) {
					if (insertPipe) {
						cout << '|';
						insertPipe = false;
					} else {
						cout << '+';
						insertPipe = true;
					}
					++column;
				} else {
					for (int i = 0; i < numberOfDashes; ++i, ++column) {
						cout << '-';
					}
				}
			}
		}
		cout << "\n";
	}


	return 0;
}