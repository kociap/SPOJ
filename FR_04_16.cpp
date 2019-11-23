#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint32;

inline uint32 max(const uint32, const uint32);
inline uint32 getBestJuiciness(const vector<uint32>& juicinesses);

int main() {
	ios::sync_with_stdio(false);

	int d;
	cin >> d;

	while (d--) {
		int n;
		cin >> n;

		vector<uint32> juicinesses;

		for (uint32 i = 0, a; i < n; ++i) {
			cin >> a;
			juicinesses.push_back(a);
		}

		cout << getBestJuiciness(juicinesses) << endl;
	}

	return 0;
}

inline uint32 max(const uint32 a, const uint32 b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}


inline uint32 getBestJuiciness(const vector<uint32>& juicinesses) {
	uint32 inclusive = juicinesses[0];
	uint32 exclusive = 0;

	for (uint32 i = 1; i < juicinesses.size(); ++i) {
		uint32 newExclusive = max(inclusive, exclusive);
		inclusive = exclusive + juicinesses[i];
		exclusive = newExclusive;
	}

	return max(inclusive, exclusive);
}
