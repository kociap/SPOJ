#include <iostream>
#include <string>
#include <unordered_map>

class Letter {
	std::string _row1;
	std::string _row2;
	std::string _row3;
public: 
	Letter();
	template<typename T> Letter(T&& row1, T&& row2, T&& row3);
	void printRow(const int& rowIndex);
	void printReversedRow(const int& rowIndex);
};

inline char toLower(char character);

int main() {
	using namespace std;
	ios::sync_with_stdio(false);

	unordered_map<char, Letter> letterMapper;
	letterMapper['a'] = Letter(" __ ", "|__|", "|  |");
	letterMapper['b'] = Letter(" __ ", "|__\\", "|__/");
	letterMapper['c'] = Letter(" __", "|  ", "|__");
	letterMapper['d'] = Letter(" __ ", "|  \\", "|__/");
	letterMapper['e'] = Letter(" __", "|_ ", "|__");
	letterMapper['f'] = Letter(" __", "|_ ", "|  ");
	letterMapper['g'] = Letter(" __ ", "| _ ", "|__|");
	letterMapper['h'] = Letter("    ", "|__|", "|  |");
	letterMapper['i'] = Letter(" ", "|", "|");
	letterMapper['j'] = Letter(" _", " |", "_|");
	letterMapper['k'] = Letter("   ", "|_/", "| \\");
	letterMapper['l'] = Letter("   ", "|  ", "|__");
	letterMapper['m'] = Letter("    ", "|\\/|", "|  |");
	letterMapper['n'] = Letter("    ", "|\\ |", "| \\|");
	letterMapper['o'] = Letter(" __ ", "|  |", "|__|");
	letterMapper['p'] = Letter(" __ ", "|__|", "|   ");
	letterMapper['r'] = Letter(" __ ", "|__|", "| \\ ");
	letterMapper['s'] = Letter(" __ ", "|__ ", " __|");
	letterMapper['t'] = Letter("___", " | ", " | ");
	letterMapper['u'] = Letter("    ", "|  |", "|__|");
	letterMapper['w'] = Letter("    ", "|  |", "|/\\|");
	letterMapper['y'] = Letter("   ", "\\_/", " | ");
	letterMapper['z'] = Letter("__", " /", "/_");
	letterMapper[' '] = Letter("  ", "  ", "  ");

	int format;
	while (true) {
		cin >> format;
		if (format == 0) {
			return 0;
		}

		string text;
		cin.get();
		getline(cin, text);

		if (format == 1) { // normal
			for (int i = 1; i <= 3; ++i) {
				for (auto textIndex = 0; textIndex < text.size(); ++textIndex) {
					letterMapper[toLower(text[textIndex])].printRow(i);
					if (textIndex + 1 != text.size() && text[textIndex + 1] != ' ') {
						cout << ' ';
					}
				}
				cout << '\n';
			}
		} else { // reversed
			for (int i = 1; i <= 3; ++i) {
				for (int textIndex = text.size() - 1; textIndex >= 0; --textIndex) {
					letterMapper[toLower(text[textIndex])].printReversedRow(i);
					if (textIndex != 0 && text[textIndex - 1] != ' ') {
						cout << ' ';
					}
				}
				cout << '\n';
			}
		}
	}

	return 0;
}

Letter::Letter(): _row1(), _row2(), _row3() {}

template<typename T> 
Letter::Letter(T&& row1, T&& row2, T&& row3): _row1(std::forward<T>(row1)), _row2(std::forward<T>(row2)), _row3(std::forward<T>(row3)) {}

void Letter::printRow(const int& rowIndex) {
	switch (rowIndex) {
	case 1:
		std::cout << _row1;
		break;
	case 2:
		std::cout << _row2;
		break;
	case 3:
		std::cout << _row3;
		break;
	}
}

void Letter::printReversedRow(const int& rowIndex) {
	auto reverseChars = [](char chr) -> char {
		switch (chr) {
		case '\\':
			return '/';
		case '/':
			return '\\';
		default:
			return chr;
		}
	};

	switch (rowIndex) {
	case 1:
		for (auto i = _row1.crbegin(); i != _row1.crend(); ++i) {
			std::cout << reverseChars(*i);
		}
		break;
	case 2:
		for (auto i = _row2.crbegin(); i != _row2.crend(); ++i) {
			std::cout << reverseChars(*i);
		}
		break;
	case 3:
		for (auto i = _row3.crbegin(); i != _row3.crend(); ++i) {
			std::cout << reverseChars(*i);
		}
		break;
	}
}

inline char toLower(char character) {
	if (character >= 65 && character <= 90) {
		return character + 32;
	} else {
		return character;
	}
}