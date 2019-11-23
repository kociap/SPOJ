#include <iostream>
#include <string>
#include <deque>
#include <math.h>

using uint64 = unsigned long long;

inline int numberOfDigits(const uint64& number) {
	return static_cast<int>(log10(number)) + 1;
}

// Digits are numbered from 0 right to left
inline int nthDigit(uint64 number, const int& n) {
	for (int i = 0; i < n; ++i) {
		number /= 10;
	}
	return number % 10;
}

inline int occurencesOf5InNumber(const std::deque<uint64>& number) {
	auto numberOf5 = 0;
	for (const auto& digit : number) {
		if (digit == 5) {
			++numberOf5;
		}
	}
	return numberOf5;
}

inline int findRightmostNon5Digit(const std::deque<uint64>& number) {
	for (int i = number.size() - 1; i >= 0; --i) {
		if (number[i] != 5) {
			return i;
		}
	}
}

int main() {
	using namespace std;
	ios::sync_with_stdio(false);

	int k; // Required number of 5s
	uint64 n; // Initial number

	cin >> n >> k;

	if (k > numberOfDigits(n)) {
		for (int i = 0; i < k; ++i) {
			cout << '5';
		}
	} else {
		auto n_copy = n + 1;
		deque<uint64> number;

		// Rewrite n_copy to number as separate digits
		for (int i = 0, numberLength = numberOfDigits(n_copy); i < numberLength; ++i) {
			number.push_front(nthDigit(n_copy, i));
		}

		while (occurencesOf5InNumber(number) < k) {
			int non5DigitIndex = findRightmostNon5Digit(number);
			if (number[non5DigitIndex] < 5) {
				number[non5DigitIndex] = 5;
			} else {
				number[non5DigitIndex] = 5;

				// Increment rest of the number
				if (non5DigitIndex > 0) {
					++number[non5DigitIndex - 1];
				} else {
					number.push_front(1);
				}

				for (int i = non5DigitIndex - 1; i >= 0; --i) {
					if (number[i] == 10 && i > 0) {
						++number[i - 1];
						number[i] = 0;
					} else {
						if (number[i] == 5) {
							number[non5DigitIndex] = 0; // reduce placed 5 to 0 if another 5 appears further in order to get maximum of k 5s
						}
						break;
					}
				}
				if (number[0] == 10) {
					number[0] = 0;
					number.push_front(1);
				}
			}
		}

		for (int i = 0; i < number.size(); ++i) {
			cout << number[i];
		}
	}

	return 0;
}