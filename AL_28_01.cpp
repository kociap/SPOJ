#include <cstdio>

using namespace std;

int main() {
	char str[30] = "";
	int length;

	scanf("%d", &length);
	scanf("%s", str);

	for (int max = length >> 1, i = 0; i <= max; ++i) {
		for (int j = 1, mid = (length >> 1) + 1; j <= length; ++j) {
			if (j >= mid - i && j <= mid + i) {
				putchar(str[j - 1]);
			} else {
				putchar('.');
			}
		}

		putchar('\n');
	}

	return 0;
}