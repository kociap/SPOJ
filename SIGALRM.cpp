#include <signal.h>

int main() {
	kill(0, 14);
	return 0;
}