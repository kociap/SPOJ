#include <cstdio>
#include <vector>

using namespace std;

inline void getNumber(vector<int> &number);
inline void multiply(vector<int> firstNumber, vector<int> secondNumber, vector<int> &result);

int main() {

	int n;
	scanf("%d", &n);

	while (n--) {
		vector<int> firstNumber;
		vector<int> secondNumber;
		vector<int> result;

		getNumber(firstNumber);
		getNumber(secondNumber);

		multiply(firstNumber, secondNumber, result);
		int i = 0, size = result.size();
		while (i + 1 < size && result[i] == 0) {
			++i;
		}
		
		for (; i < size; ++i) {
			putchar((char)result[i] + 48);
		}
		putchar('\n');
	}

	return 0;
}

inline void getNumber(vector<int> &number) {
	char c = getchar();

	while (c == ' ' || c == '\n') {
		if (c == EOF) {
			break;
		}

		c = getchar();
	}

	while ((char)c >= 48 && (char)c <= 57) {
		number.push_back((int)c - 48);
		c = getchar();
	}

}

inline void multiply(vector<int> firstNumber, vector<int> secondNumber, vector<int> &result) {
	int firstNumberSize = firstNumber.size();
	int secondNumberSize = secondNumber.size();
	result.resize(firstNumberSize + secondNumberSize, 0);

	// Multiply numbers
	for (int i = firstNumberSize - 1; i >= 0; --i) {
		for (int j = secondNumberSize - 1; j >= 0; --j) {
			result[i + j + 1] += firstNumber[i] * secondNumber[j];
		}
	}

	// Mod result to flatten it
	for (int i = firstNumberSize + secondNumberSize - 1, forward = 0; i >= 0; --i) {
		result[i] += forward;

		if (result[i] > 9) {
			forward = result[i] / 10;
			result[i] %= 10;
		} else {
			forward = 0;
		}
	}
}

inline void karatsubaMultiplication(vector<int> firstNumber, vector<int> secondnNumber, vector<int> &result) {

}