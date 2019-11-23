//#include <cstdio>
//#include <vector>
//
//using namespace std;
//
//inline bool getLine(vector<char> &str);
//
//int main() {
//
//	vector<char> sentence;
//
//	while (getLine(sentence)) {
//		vector<char> decipheredSentence;
//		vector<vector<char> > words(1);
//		int sentenceSize = sentence.size();
//
//		for (int i = 0, wordsIter = 0; i < sentenceSize; ++i) {
//			if (sentence[i] != ' ') {
//				words[wordsIter].push_back(sentence[i]);
//			} else {
//				++wordsIter;
//				words.resize(wordsIter + 1);
//			}
//		}
//
//		int numberOfWords = words.size();
//		decipheredSentence.push_back(words[numberOfWords - 1][0]);
//
//		for (int wordsIter = 0; wordsIter < numberOfWords; wordsIter++) {
//			for (int i = words[wordsIter].size() - 1; i > 0; --i) {
//				decipheredSentence.push_back(words[wordsIter][i]);
//			}
//
//			if (wordsIter + 1 < numberOfWords) {
//				decipheredSentence.push_back(' ');
//				decipheredSentence.push_back(words[wordsIter][0]);
//			}
//		}
//
//		for (int i = 0, decipheredSentenceSize = decipheredSentence.size(); i < decipheredSentenceSize; ++i) {
//			putchar(decipheredSentence[i]);
//		}
//		putchar('\n');
//	}
//
//	return 0;
//}
//
//inline bool getLine(vector<char>& str) {
//	str.clear();
//
//	char c = getchar();
//
//	while (c == '\n') {
//		c = getchar();
//	}
//
//	if (c == EOF) {
//		return false;
//	}
//
//	while (c != '\n') {
//		str.push_back(c);
//		c = getchar();
//	}
//
//	return true;
//}
