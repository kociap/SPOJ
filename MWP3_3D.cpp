#include <cstdio>

using namespace std;

int main() {

	const double PI = 3.141592653589793;

	int t;
	scanf("%d", &t);

	while (t--) {
		double diameter;
		int peopleWillingToEat;
		scanf("%lf %d", &diameter, &peopleWillingToEat);

		double pizzaPieceLength = diameter / peopleWillingToEat * PI;
		if ((peopleWillingToEat & 1) == 1) {
			pizzaPieceLength /= 2;
			peopleWillingToEat
		}

		printf("%.3f %d\n", pizzaPieceLength, peopleWillingToEat);
	}

	return 0;
}