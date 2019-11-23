#include <cstdio>
#include <vector>

using namespace std;

class City {
public:
	int numberOfConnections;
	vector<int> connections;

	City() {
		numberOfConnections = 0;
	}
};

inline long long findTriples(vector<City*>cities, int index);

int main() {

	int numberOfHotels;
	long long numberOfTriples = 0;
	vector<City*>cities;

	scanf("%d", &numberOfHotels);
	cities.resize(numberOfHotels);
	for (int i = 1, a, b; i < numberOfHotels; ++i) {
		scanf("%d %d", &a, &b);
		cities[a - 1]->connections.push_back(b);
		cities[a - 1]->numberOfConnections++;
		cities[b - 1]->connections.push_back(a);
		cities[b - 1]->numberOfConnections++;
	}

	for (int i = 0; i < numberOfHotels; ++i) {
		numberOfTriples += findTriples(cities, i);
	}

	printf("%lld\n", numberOfTriples);

	return 0;
}

inline long long findTriples(vector<City*>cities, int index) {
	if (cities[index]->numberOfConnections < 3) {
		return 0;
	} else {
		long long numberOfPossibleLocations = 0;
		const long long pathsOut = cities[index]->numberOfConnections;
		int numberOfPathsAvailable = cities[index]->numberOfConnections;
		vector<int>roots(1, index);
		vector< int > leaves();
		roots.reserve(5000);
		leaves.resize(pathsOut);

		while (numberOfPathsAvailable > 3) {
			long long coefficient = 1;
			for (int i = 0; i < pathsOut; ++i) {
				int leavesSize = leaves[i].size();
				if (leaves[i].size() > 0) {

				}
			}
		}

		return numberOfPossibleLocations;
	}
}