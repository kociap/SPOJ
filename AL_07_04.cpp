#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

inline void generatePrimes(vector<int>& primes, const int max);
inline void buildTree(vector<int> &tree, const int &numberOfSeats);
inline int erase(vector<int> &tree, const int index, const int lookFor);
inline int find(const vector<int> &tree, const int index, const int lookFor);
inline int leftChild(const int index);
inline int rightChild(const int index);
inline int parent(const int index);
inline int indexOf(const int index, const int m);

int main() {
	ios::sync_with_stdio(false);

	vector<int> primes;
	generatePrimes(primes, 1299709);

	int n;
	cin >> n;

	while (n--) {
		// Number of seats
		int m;
		cin >> m;

		vector<int> seats;
		buildTree(seats, m);

		int primeIndex = 0;
		int numberOfSeats = m;
		int lastPosition = 1;
		while (numberOfSeats > 1) {
			lastPosition = (primes[primeIndex] + (lastPosition == 0 ? 1 : lastPosition) - 1) % numberOfSeats;
			erase(seats, 0, lastPosition == 0 ? numberOfSeats : lastPosition);
			++primeIndex;
			--numberOfSeats;
		}
		
		cout << indexOf(find(seats, 0, 1), m) << endl;
	}

	return 0;
}

inline void generatePrimes(vector<int>& primes, int max) {
	int maxSqrt = sqrt(max);
	vector<bool> isPrime(max + 1, true);

	for (int i = 2; i <= maxSqrt; ++i) {
		if (isPrime[i]) {
			for (int j = i * i; j <= max; j += i << 1) {
				isPrime[j] = false;
			}
		}
	}

	primes.push_back(2);
	for (int i = 3; i <= max; i += 2) {
		if (isPrime[i]) {
			primes.push_back(i);
		}
	}
}

inline void buildTree(vector<int>& tree, const int &numberOfSeats) {
	int numberOfAllocatedLeaves = 1;
	tree.push_back(0);

	while (numberOfAllocatedLeaves < numberOfSeats) {
		numberOfAllocatedLeaves <<= 1;
		int pushValue = (numberOfAllocatedLeaves < numberOfSeats ? 0 : 1);
		for (int i = 0; i < numberOfAllocatedLeaves && i < numberOfSeats; ++i) {
			tree.emplace_back(pushValue);
		}
	}

	for (int i = tree.size() - 1; i > 0; --i) {
		tree[parent(i)] += tree[i];
	}
}

inline int erase(vector<int>& tree, const int index, const int lookFor) {
	--tree[index];
	if (leftChild(index) >= tree.size()) {
		tree[index] = 0;
		return index;
	}

	if (tree[leftChild(index)] >= lookFor) {
		return erase(tree, leftChild(index), lookFor);
	} else {
		return erase(tree, rightChild(index), lookFor - tree[leftChild(index)]);
	}
}

inline int find(const vector<int>& tree, const int index, const int lookFor) {
	if (leftChild(index) >= tree.size()) {
		return index;
	}

	if (tree[leftChild(index)] == lookFor) {
		return find(tree, leftChild(index), lookFor);
	} else {
		return find(tree, rightChild(index), lookFor);
	}
}

inline int leftChild(const int index) {
	return (index << 1) + 1;
}

inline int rightChild(const int index) {
	return (index << 1) + 2;
}

inline int parent(const int index) {
	return (index - 1) >> 1;
}

inline int indexOf(const int index, const int m) {
	int n = 0;
	if (n == 0) {
		n = 1;
		while (n < m) {
			n <<= 1;
		}
	}

	return index - n + 2;
}
