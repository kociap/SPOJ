#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false);

	constexpr int cups_number = 5;

	struct Volume {
		long long volume;
		int index;
	};

	std::vector<Volume> volumes(cups_number);
	long long volumes_sum = 0;

	for(int i = 0; i < cups_number; ++i) {
		std::cin >> volumes[i].volume;
		volumes[i].index = i + 1;
		volumes_sum += volumes[i].volume;
	}

	std::sort(volumes.begin(), volumes.end(), [](Volume const& a, Volume const& b) { return a.volume < b.volume; });

	for(int i = 0; i < cups_number; ++i) {
		int left = 0, right = cups_number - 1;
		while(left != right) {
			long long sum = 3 * (volumes[left].volume + volumes[right].volume) + volumes[i].volume;
			if(sum == volumes_sum) {
				std::cout << volumes[i].index;
				return 0;
			} else if(sum < volumes_sum) {
				++left;
			} else {
				--right;
			}
		}
	}

    return 0;
}

