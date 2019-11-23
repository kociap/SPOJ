#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

inline void FisherYatesShuffle(int array[], int start, int length);
inline void quickSort(int array[], int left, int right);
inline int quickSortPartition(int array[], int left, int right);
inline int binarySearch(int flowerfulnesses[], int left, int right, int toFind);

int main() {

	srand(time(NULL));

	int n, m;
	int minDifference = 1000100000;
	scanf("%d", &n);
	int *flowerfulness = new int[n + 2];
	flowerfulness[0] = -1000000100;
	flowerfulness[n + 1] = 2000000200;

	for (int i = 1, a; i <= n; ++i) {
		scanf("%d", &a);
		flowerfulness[i] = a;
	}

	FisherYatesShuffle(flowerfulness, 1, n);
	quickSort(flowerfulness, 1, n);

	scanf("%d", &m);

	for (int i = 0, a; i < m; ++i) {
		scanf("%d", &a);
		int searchResult = binarySearch(flowerfulness, 1, n, a);
		if (searchResult < minDifference) {
			minDifference = searchResult;
		}
	}

	printf("%d", minDifference);

	delete flowerfulness;

	return 0;
}

inline void FisherYatesShuffle(int array[], int start, int end) {
	for (int i = end, randomized; i > start; --i) {
		randomized = rand() % (i - 1) + 1;
		swap(array[i], array[randomized]);
	}
}

inline void quickSort(int array[], int left, int right) {
	if (left < right) {
		int middle = quickSortPartition(array, left, right);
		quickSort(array, left, middle - 1);
		quickSort(array, middle + 1, right);
	}
}

inline int quickSortPartition(int array[], int left, int right) {
	int current = left;

	for (int i = left; i < right; ++i) {
		if (array[i] < array[right]) {
			swap(array[i], array[current]);
			current++;
		}
	}

	swap(array[right], array[current]);

	return current;
}

inline int binarySearch(int flowerfulnesses[], int left, int right, int toFind) {
	// Requires sentinel values
	// Left sentinel = -10^9 - 5
	// Right sentinel = 10^9 * 2 + 5

	int middle = (left + right) >> 1;

	if (flowerfulnesses[middle] == toFind) {
		return 0;
	} else {
		if (flowerfulnesses[middle] > toFind) {
			if (flowerfulnesses[middle - 1] <= toFind) {
				return (toFind - flowerfulnesses[middle - 1] < flowerfulnesses[middle] - toFind ? toFind - flowerfulnesses[middle - 1] : flowerfulnesses[middle] - toFind);
			} else {
				return binarySearch(flowerfulnesses, left, middle - 1, toFind);
			}
		} else {
			if (flowerfulnesses[middle + 1] >= toFind) {
				return (flowerfulnesses[middle + 1] - toFind < toFind - flowerfulnesses[middle] ? flowerfulnesses[middle + 1] - toFind : toFind - flowerfulnesses[middle]);
			} else {
				return binarySearch(flowerfulnesses, middle + 1, right, toFind);
			}
		}
	}
}
