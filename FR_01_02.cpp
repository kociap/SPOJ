#include <cstdio>

using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b);

int main() {

	unsigned long long a, b, c, d;

	scanf("%llu/%llu %llu/%llu", &a, &b, &c, &d);

	unsigned long long denominatorGCD = gcd(b, d);
	unsigned long long denominatorLCM = b * d / denominatorGCD;

	unsigned long long nominatorA = denominatorLCM / b * a;
	unsigned long long nominatorC = denominatorLCM / d * c;
	unsigned long long nominator = denominatorLCM / b * a + denominatorLCM / d * c;
	unsigned long long newGCD = gcd(nominator, denominatorLCM);

	printf("%llu/%llu + %llu/%llu = %llu/%llu", a, b, c, d, nominator / newGCD, denominatorLCM / newGCD);

	return 0;
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
	unsigned long long c;

	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}

	return a;
}
