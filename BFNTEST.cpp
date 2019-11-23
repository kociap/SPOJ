#include <cstdio>
#include <vector>

using namespace std;

int main() {

	vector<char>input;

	char c = getchar();

	while (c != EOF) {
		input.push_back(c);
		c = getchar();
	}

	int inputLength = input.size();
	bool blockComment = false;
	bool lineComment = false;
	bool str = false;

	for (int i = 0; i < inputLength; ++i) {
		char currentChar = input[i];
		if (!lineComment && !blockComment) {
			if (input[i] == '\"') {
				if (input[i - 1] == '\\') {
					putchar('\"');
					continue;
				} else {
					str = !str;
					putchar('\"');
					continue;
				}
			}
		}

		if (!str) {
			if (lineComment && input[i] != '\n') {
				continue;
			} else if (lineComment && input[i] == '\n') {
				if (input[i - 1] == '\\') {
					continue;
				} else {
					lineComment = false;
					putchar('\n');
					continue;
				}
			}
			
			if (blockComment && input[i] != '*') {
				continue;
			} else if (blockComment && input[i] == '*' && input[i + 1] == '/') {
				blockComment = false;
				i++;
				continue;
			} else if (blockComment && input[i] == '*' && input[i + 1] != '/') {
				continue;
			}
		}

		if (input[i] != '/') {
			putchar(input[i]);
			continue;
		} else {
			if(!str) {
				if (input[i + 1] == '*') {
					blockComment = true;
					i++;
					continue;
				} else if (input[i + 1] == '/') {
					lineComment = true;
					i++;
					continue;
				} else {
					putchar(input[i]);
				}
			} else {
				putchar(input[i]);
			}
		}
	}

	return 0;
}