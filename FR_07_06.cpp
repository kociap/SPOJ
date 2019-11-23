//#include <iostream>
//
//using namespace std;
//
//typedef unsigned long long uint64;
//
//
//inline void getNumber(uint64 &number);
//
//int main() {
//	ios::sync_with_stdio(false);
//
//	uint64 queries;
//	getNumber(queries);
//	while (queries--) {
//		uint64 size;
//		uint64 numberOfSquares = 0;
//		getNumber(size);
//		printf("%llu\n", (2ULL * size * size * size + 3ULL * size * size + size) / 6ULL);
//	}
//
//	return 0;
//}
//
//inline void getNumber(uint64 &number) {
//	number = 0;
//	char c = cin.get();
//
//	while ((c < 48 || c > 57) && c != EOF) {
//		c = cin.get();
//	}
//
//	while (c >= 48 && c <= 57) {
//		number *= 10;
//		number += c - 48;
//		c = cin.get();
//	}
//}
