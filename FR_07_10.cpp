#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct CodeCharacter {
	bool wasUsed = false;
	char character;

	explicit CodeCharacter(char a): character(a) {}
};

inline bool readLine(vector<CodeCharacter> &line) {
	char c = cin.get();

	while (c == '\n') {
		c = cin.get();
	}

	if (c == EOF) {
		return false;
	}

	while (c != '\n' && c != EOF) {
		line.emplace_back(c);
		c = cin.get();
	}

	return true;
}

inline int getNextLetterIndex(vector<CodeCharacter> &encryptedMessage, int currentIndex, int offset) {
	currentIndex += offset;

	if (currentIndex >= encryptedMessage.size()) {
		currentIndex %= encryptedMessage.size();
	}

	while (encryptedMessage[currentIndex].wasUsed) {
		++currentIndex;
	}

	return currentIndex;
}

int main() {
	ios::sync_with_stdio(false);

	while (true) {
		vector<CodeCharacter> line;

		if (!readLine(line)) {
			break;
		}

		int currentIndex = 0;
		int offset = sqrt(line.size());

		// First char is always first
		line[0].wasUsed = true;
		cout << line[0].character;
		for (int i = 1; i < line.size(); ++i) {
			currentIndex = getNextLetterIndex(line, currentIndex, offset);
			line[currentIndex].wasUsed = true;
			cout << line[currentIndex].character;
		}
		cout << endl;
	}

	return 0;
}