#include <cstdio>

using namespace std;

int main() {

	int q;
	scanf("%d", &q);

	while (q--) {
		int numberOfPlaces, indexOfQuestioner;
		scanf("%d %d", &numberOfPlaces, &indexOfQuestioner);

		if ((numberOfPlaces & 1) == 1) {
			printf("BRAK\n");
		} else {
			if (indexOfQuestioner > (numberOfPlaces >> 1)) {
				printf("%d\n", indexOfQuestioner - (numberOfPlaces >> 1));
			} else {
				printf("%d\n", indexOfQuestioner + (numberOfPlaces >> 1));
			}
		}
	}

	return 0;
}