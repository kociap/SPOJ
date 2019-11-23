#include <cstdio>
#include <vector>

using namespace std;

class Sequence {
public:
	int lastElement = 0;
	int length = 0;

	Sequence() {}

	Sequence(int element) {
		lastElement = element;
		length = 1;
	}

	Sequence(int element, int sequenceLength) {
		lastElement = element;
		length = sequenceLength;
	}
};

inline int binarySearchIncreasing(const vector<Sequence> &sequences, const int left, const int right, const int toFind);
inline int getInt();

int main() {
	int t = getInt();

	while (t--) {
		vector<int> trees;
		int maxPath = 0;
		int numberOfTrees = getInt();

		for (int i = 0, a; i < numberOfTrees; ++i) {
			a = getInt();
			trees.push_back(a);
		}

		// Monotonous increasing sequences
		vector<Sequence> increasingSequences;
		int numberOfIncreasingSequences = 1;
		increasingSequences.push_back(Sequence(trees[0]));

		for (int i = 1; i < numberOfTrees; ++i) {
			// Find sequence ending with greatest smaller or equal to given element
			int index = binarySearchIncreasing(increasingSequences, 0, numberOfIncreasingSequences - 1, trees[i]);

			if (index == -1) {
				// If element is smaller than shortest sequence
				increasingSequences[0].lastElement = trees[i];
			} else {
				if (index + 1 == numberOfIncreasingSequences) {
					increasingSequences.push_back(Sequence(trees[i], increasingSequences[index].length + 1));
					++numberOfIncreasingSequences;
				} else {
					increasingSequences[index + 1].lastElement = trees[i];
				}
			}
		}

		// Monotonous decreasing sequences
		vector<Sequence> decreasingSequences;
		int numberOfDecreasingSequences = 1;
		decreasingSequences.push_back(Sequence(trees[numberOfTrees - 1]));

		for (int i = numberOfTrees - 2; i >= 0; --i) {
			int index = binarySearchIncreasing(decreasingSequences, 0, numberOfDecreasingSequences - 1, trees[i]);

			if (index == -1) {
				decreasingSequences[0].lastElement = trees[i];
			} else {
				if (index + 1 == numberOfDecreasingSequences) {
					decreasingSequences.push_back(Sequence(trees[i], decreasingSequences[index].length + 1));
					++numberOfDecreasingSequences;
				} else {
					decreasingSequences[index + 1].lastElement = trees[i];
				}
			}
		}

		int longestIncreasingSequence = increasingSequences[numberOfIncreasingSequences - 1].length;
		int longestDecreasingSequence = decreasingSequences[numberOfDecreasingSequences - 1].length;

		printf("%d\n", numberOfTrees - (longestDecreasingSequence > longestIncreasingSequence ? longestDecreasingSequence : longestIncreasingSequence));
	}

	return 0;
}

inline int binarySearchIncreasing(const vector<Sequence> &sequences, const int left, const int right, const int toFind) {
	const int middle = (left + right) >> 1;

	if ((sequences[middle].lastElement <= toFind && middle == right) || (sequences[middle].lastElement <= toFind && sequences[middle + 1].lastElement > toFind)) {
		return middle;
	} else if (sequences[middle].lastElement > toFind) {
		if (middle <= 0) {
			return -1;
		}

		return binarySearchIncreasing(sequences, left, middle - 1, toFind);
	} else {
		return binarySearchIncreasing(sequences, middle + 1, right, toFind);
	}
}

inline int getInt() {
	char c = getchar();

	while (c < 48 || c > 57) {
		c = getchar();
	}

	int number = c - 48;

	c = getchar();
	while (c >= 48 && c <= 57) {
		number *= 10;
		number += c - 48;

		c = getchar();
	}

	return number;
}