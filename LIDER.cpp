//#include <cstdio>
//#include <vector>
//
//using namespace std;
//
//typedef unsigned long long uint64;
//
//inline bool getUint64(uint64& a);
//
//int main() {
//	int t;
//	scanf("%d", &t);
//	
//	while (t--) {
//		vector<uint64> numbers;
//		uint64 n;
//		scanf("%llu", &n);
//		for (uint64 a, i = 0; i < n; ++i) {
//			getUint64(a);
//			//printf("%llu\n", i);
//			numbers.push_back(a);
//		}
//
//		uint64 candidate = -1;
//		uint64 occurences = 1;
//		for (uint64 i = 0; i < n; ++i) {
//			if (numbers[i] == candidate) {
//				++occurences;
//			} else {
//				--occurences;
//			}
//
//			if (occurences == 0) {
//				candidate = numbers[i];
//				occurences = 1;
//			}
//		}
//
//		occurences = 0;
//		for (uint64 i = 0; i < n; ++i) {
//			if (numbers[i] == candidate) {
//				++occurences;
//			}
//		}
//
//		if (occurences > (n >> 1)) {
//			printf("%llu\n", candidate);
//		} else {
//			printf("-1\n");
//		}
//	}
//
//	return 0;
//}
//
//inline bool getUint64(uint64& a) {
//	a = 0;
//	char c = getchar();
//
//	if (c == '\n') {
//		c = getchar();
//	}
//
//	if (c == EOF) {
//		return false;
//	}
//
//	while (c >= 48 && c <= 57) {
//		a *= 10;
//		a += c - 48;
//		c = getchar();
//	}
//
//	return true;
//}