//#include <cstdio>
//
//using namespace std;
//
//typedef unsigned long long uint64;
//
//inline uint64 gcd(uint64 a, uint64 b);
//
//int main() {
//
//	uint64 a, b, c, s;
//	scanf("%llu %llu %llu %llu", &a, &b, &c, &s);
//
//	// Convert to centimeters
//	s *= 100;
//
//	uint64 abLCM = a / gcd(a, b) * b;
//	uint64 abcLCM = abLCM / gcd(c, abLCM) * c;
//
//	printf("%llu", s / abcLCM);
//
//	return 0;
//}
//
//inline uint64 gcd(uint64 a, uint64 b) {
//	uint64 c;
//
//	while (b != 0) {
//		c = a % b;
//		a = b;
//		b = c;
//	}
//
//	return a;
//}
