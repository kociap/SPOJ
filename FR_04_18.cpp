#include <iostream>
#include <deque>
#include <unordered_map>

using namespace std;

inline void getFullLine(deque<char>& line);
inline int parseParentheses(deque<char>& expression, unordered_map<char, int>& variables, int& index);
inline int parseExpression(deque<char> &expression, int &index, unordered_map<char, int>& variables);

inline bool isSign(char a) { return a == '+' || a == '-'; }
inline bool isVariable(char a) { return a == 'x' || a == 'y' || a == 'z'; }
inline bool isNumber(char a) { return a >= 48 && a <= 57; }
inline bool isOpeningParenthesis(char a) { return a == '('; }
inline bool isEnclosingParenthesis(char a) { return a == ')'; }

int main() {
	// ios::sync_with_stdio(false); // Cannot use with getchar

	int d;
	// x, y, z
	unordered_map<char, int> variables;
	cin >> d >> variables['x'] >> variables['y'] >> variables['z'];

	while (d--) {
		deque<char> expression;
		getFullLine(expression);

		expression.push_front('(');
		expression.push_back(')');
		int index = 1;
		int result = parseParentheses(expression, variables, index);
		cout << result << endl;
	}

	return 0;
}

inline void getFullLine(deque<char>& line) {
	char c = getchar();

	while (c == '\n') {
		c = getchar();
	}

	while (c != '\n' && c != EOF) {
		line.push_back(c);
		c = getchar();
	}
}

inline int parseParentheses(deque<char>& expression, unordered_map<char, int>& variables, int& index) {
	deque<int>terms;
	deque<char>operators;

	int number;
	while (!isEnclosingParenthesis(expression[index])) {
		const int preParsingIndex = index;
		// get next term
		if (isSign(expression[index]) || isNumber(expression[index]) || isVariable(expression[index])) {
			number = parseExpression(expression, index, variables);
		} else {
			++index;
			number = parseParentheses(expression, variables, index);
		}
		terms.push_back(number);

		// guess operator
		if (!isOpeningParenthesis(expression[preParsingIndex - 1])) {
			if (isSign(expression[preParsingIndex])) {
				operators.push_back('+');
			} else {
				operators.push_back('*');
			}
		}
	}

	++index;

	for (int i = 0; i < operators.size(); ++i) {
		if (operators[i] == '*') {
			terms[i] = terms[i] * terms[i + 1];
			terms.erase(terms.begin() + i + 1);
			operators.erase(operators.begin() + i);
			--i;
		}
	}

	int result = 0;
	for (int i = 0; i < terms.size(); ++i) {
		result += terms[i];
	}

	return result;
}

inline int parseExpression(deque<char> &expression, int &index, unordered_map<char, int>& variables) {
	int number = 1;

	if (isSign(expression[index])) {
		number *= expression[index] == '-' ? -1 : 1;
		++index;
	}

	while (isVariable(expression[index]) || isNumber(expression[index])) {
		if (isNumber(expression[index])) {
			number *= expression[index] - 48;
		} else {
			number *= variables[expression[index]];
		}
		++index;
	}

	return number;
}
