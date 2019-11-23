#include <cstdio>
//#include <cstdlib>
//#include <ctime>
#include <vector>

using namespace std;

inline void fisherYatesShuffle(vector<long long> &pokemons, const int size);
//inline int quickSortPartition(vector<long long> &pokemons, int left, int right);
//inline void quickSort(vector<long long> &pokemons, const int left, const int right);
inline void mergeSort(vector<long long> &pokemons, const int left, const int right);
inline int binarySearch(const vector<long long> &pokemons, const int left, const int right, const long long toFind);

int main() {

	//srand(time(NULL));

	int numberOfPlayers;
	scanf("%d", &numberOfPlayers);
	vector<long long> pokemons;

	for (int i = 0; i < numberOfPlayers; ++i) {
		long long a;
		scanf("%lld", &a);
		pokemons.push_back(a);
	}

	pokemons.push_back(9223372036854775807LL);

	//fisherYatesShuffle(pokemons, numberOfPlayers - 1);
	mergeSort(pokemons, 0, numberOfPlayers - 1);

	int numberOfQuestions;
	scanf("%d", &numberOfQuestions);

	for (int i = 0; i < numberOfQuestions; ++i) {
		long long maxNumberOfPokemons;
		scanf("%lld", &maxNumberOfPokemons);

		int index = binarySearch(pokemons, 0, numberOfPlayers - 1, maxNumberOfPokemons);
		printf("%d\n", numberOfPlayers - index - 1);
	}

	return 0;
}

//inline void fisherYatesShuffle(vector<long long>& pokemons, const int size) {
//	for (int i = size; i > 0; --i) {
//		swap(pokemons[i], pokemons[rand() % i]);
//	}
//}

//inline int quickSortPartition(vector<long long>& pokemons, int left, int right) {
//	int partsSeparator = left;
//
//	for (int i = left; i < right; ++i) {
//		if (pokemons[i] < pokemons[right]) {
//			swap(pokemons[i], pokemons[partsSeparator]);
//			++partsSeparator;
//		}
//	}
//
//	swap(pokemons[partsSeparator], pokemons[right]);
//
//	return partsSeparator;
//}
//
//inline void quickSort(vector<long long>& pokemons, const int left, const int right) {
//	if (left < right) {
//		int middle = quickSortPartition(pokemons, left, right);
//
//		quickSort(pokemons, left, middle - 1);
//		quickSort(pokemons, middle + 1, right);
//	}
//}

inline void mergeSort(vector<long long> &pokemons, const int left, const int right) {
	if (left < right) {
		int middle = (left + right) >> 1;

		mergeSort(pokemons, left, middle);
		mergeSort(pokemons, middle + 1, right);

		vector<long long>leftPart(pokemons.begin() + left, pokemons.begin() + middle + 1);
		vector<long long>rightPart(pokemons.begin() + middle + 1, pokemons.begin() + right + 1);
		leftPart.push_back(9223372036854775807LL);
		rightPart.push_back(9223372036854775807LL);

		vector<long long>::iterator leftPartIterator = leftPart.begin();
		vector<long long>::iterator rightPartIterator = rightPart.begin();

		for (int i = 0, length = right - left + 1; i < length; ++i) {
			if (*leftPartIterator < *rightPartIterator) {
				pokemons[i + left] = *leftPartIterator;
				++leftPartIterator;
			} else {
				pokemons[i + left] = *rightPartIterator;
				++rightPartIterator;
			}
		}
	}
}

inline int binarySearch(const vector<long long>& pokemons, const int left, const int right, const long long toFind) {
	const int middle = (left + right) >> 1;

	if (pokemons[middle] == toFind && pokemons[middle + 1] > toFind) {
		return middle;
	} else {
		if (pokemons[middle] > toFind) {
			return binarySearch(pokemons, left, middle - 1, toFind);
		} else {
			return binarySearch(pokemons, middle + 1, right, toFind);
		}
	}
}
