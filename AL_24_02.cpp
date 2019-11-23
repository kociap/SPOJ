//#include <cstdio>
//
//using namespace std;
//
//typedef unsigned long long uint64;
//
//inline bool findBlockType(const uint64 left, const uint64 right, const uint64 toFind, bool block);
//
//int main() {
//
//	int t;
//	scanf("%d", &t);
//
//	while (t--) {
//		uint64 n;
//		const uint64 LEFT_BOUNDARY = 0;
//		const uint64 RIGHT_BOUNDARY = 1152921504606846976;
//		scanf("%llu", &n);
//
//		uint64 numberOfCaresses = n >> 2 << 1;
//
//		if ((numberOfCaresses << 1) == n) {
//			// If n is a multiple of 4, we are done
//			printf("%llu %llu\n", numberOfCaresses, numberOfCaresses);
//		} else {
//			uint64 firstCatCaresses = 0;
//			uint64 secondCatCaresses = 0;
//			bool blockType = findBlockType(LEFT_BOUNDARY, RIGHT_BOUNDARY, n, false);
//			if (blockType) {
//				// Block type: 2112
//				uint64 blockOverflow = n - (numberOfCaresses << 1);
//				if (blockOverflow > 2) {
//					firstCatCaresses += 2;
//					++secondCatCaresses;
//				} else if (blockOverflow > 1) {
//					++firstCatCaresses;
//					++secondCatCaresses;
//				} else {
//					++secondCatCaresses;
//				}
//			} else {
//				// Block type: 1221
//				uint64 blockOverflow = n - (numberOfCaresses << 1);
//				if (blockOverflow > 2) {
//					secondCatCaresses += 2;
//					++firstCatCaresses;
//				} else if (blockOverflow > 1) {
//					++secondCatCaresses;
//					++firstCatCaresses;
//				} else {
//					++firstCatCaresses;
//				}
//			}
//
//			printf("%llu %llu\n", numberOfCaresses + firstCatCaresses, numberOfCaresses + secondCatCaresses);
//		}
//	}
//
//	return 0;
//}
//
//inline bool findBlockType(const uint64 left, const uint64 right, const uint64 toFind, bool block) {
//	const uint64 interval = (right - left) >> 2;
//
//	if (interval == 1) {
//		return block;
//	} else {
//		if (left + (interval << 1) > toFind) {
//			if (left + interval >= toFind) {
//				return findBlockType(left, left + interval, toFind, block);
//			} else {
//				return findBlockType(left + interval, left + (interval << 1), toFind, !block);
//			}
//		} else {
//			if (left + (interval << 1) + interval > toFind) {
//				return findBlockType(left + (interval << 1), left + (interval << 1) + interval, toFind, !block);
//			} else {
//				return findBlockType(left + (interval << 1) + interval, right, toFind, block);
//			}
//		}
//	}
//}
//
////Rubbish Dump
////5x Bloodstones
//// warshard
//// warshard
//// Doom safe
//// 20 diamonds
//// greed shard
//// cookie jar
//// greed shard