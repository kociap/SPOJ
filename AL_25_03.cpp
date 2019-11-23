#include <iostream>
#include <string>

inline bool isDivisibleBy343(const std::string& number);

int main() {
	using namespace std;
	ios::sync_with_stdio(false);

	int t;
	cin >> t;
	while (t--) {
		string number;
		cin >> number;

		using uint32 = unsigned int;

		uint32 sum = 0;
		uint32 alternateSum = 0;
		for (auto i = 0; i < number.size(); ++i) {
			sum += number[i] - 48;
			if ((i & 1) == 1) {
				alternateSum -= number[i] - 48;
			} else {
				alternateSum += number[i] - 48;
			}
		}
	
		if (sum % 6 == 0) {
			cout << "TAK ";
		} else {
			cout << "NIE ";
		}

		if (alternateSum % 8 == 0) {
			cout << "TAK ";
		} else {
			cout << "NIE ";
		}

		if (isDivisibleBy343(number)) {
			cout << "TAK" << endl;
		} else {
			cout << "NIE" << endl;
		}
	}

	return 0;
}

inline bool isDivisibleBy343(const std::string& number) {
	return (number.size() > 3 && number[number.size() - 1] == '0' && number[number.size() - 2] == '0' && number[number.size() - 3] == '0')
		   || (number.size() == 1 && number[0] == '0');
}
