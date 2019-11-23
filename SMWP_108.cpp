#include <iostream>
#include <vector>

using namespace std;

using int64 = long long;

// Heap operations
inline int64 max(vector<int64>&);
inline int64 extractMax(vector<int64>&);
inline void insert(vector<int64>&, int64);
inline void maxHeapifyUp(vector<int64>&, int);
inline void maxHeapifyDown(vector<int64>&, int);
inline int parent(int);
inline int leftChild(int);
inline int rightChild(int);

int main() {
	ios::sync_with_stdio(false);

	int t;
	cin >> t;

	vector<int64> heap;
	int heapSize = 0;

	while (t--) {
		char action;
		cin >> action;

		if (action == 'a') {
			int numberOfPeopleArrived;
			cin >> numberOfPeopleArrived;

			for (int i = 0; i < numberOfPeopleArrived; ++i) {
				long long priority;
				cin >> priority;

				insert(heap, priority);

				++heapSize;
			}
		} else if (action == 'r') {
			int trainSize;
			cin >> trainSize;

			while (trainSize > 0 && heapSize > 0) {
				extractMax(heap);

				--heapSize;
				--trainSize;
			}
		} else if(action == 'c') {
			cout << heapSize << endl;
		}  else if (action == 'p') {
			if (heapSize > 0) {
				cout << max(heap) << endl;
			} else {
				cout << '0' << endl;
			}
		}
	}

	return 0;
}

inline int64 max(vector<int64>& heap) {
	return heap[0];
}

inline int64 extractMax(vector<int64>& heap) {
	int64 max = heap[0];

	swap(*heap.begin(), *--heap.end());
	heap.pop_back();

	maxHeapifyDown(heap, 0);

	return max;
}

inline void insert(vector<int64>& heap, int64 element) {
	heap.push_back(element);
	maxHeapifyUp(heap, heap.size() - 1);
}

inline void maxHeapifyUp(vector<int64>& heap, int index) {
	int parentIndex = parent(index);

	while (parentIndex != index && heap[parentIndex] < heap[index]) {
		swap(heap[parentIndex], heap[index]);
		index = parentIndex;
		parentIndex = parent(parentIndex);
	}
}

inline void maxHeapifyDown(vector<int64>& heap, int index) {
	if (rightChild(index) < heap.size()) {
		if (heap[rightChild(index)] > heap[leftChild(index)]) {
			if (heap[rightChild(index)] > heap[index]) {
				swap(heap[rightChild(index)], heap[index]);
				maxHeapifyDown(heap, rightChild(index));
			}
		} else if (heap[leftChild(index)] > heap[index]) {
			swap(heap[leftChild(index)], heap[index]);
			maxHeapifyDown(heap, leftChild(index));
		}
	} else if(leftChild(index) < heap.size() && heap[leftChild(index)] > heap[index]) {
		swap(heap[leftChild(index)], heap[index]);
		maxHeapifyDown(heap, leftChild(index));
	}
}

inline int parent(int i) {
	return i >> 1;
}

inline int leftChild(int i) {
	return i << 1;
}

inline int rightChild(int i) {
	return (i << 1) + 1;
}