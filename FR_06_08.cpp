#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

inline void readTime(vector<char> &time);
inline double getMinuteHandAngle(int &minutes);
inline double getHourHandAngle(int &hours, int &minutes);

int main() {
	ios::sync_with_stdio(false);

	int t;
	cin >> t;
	while (t--) {
		vector<char> time;
		readTime(time);

		int hours;
		int minutes;

		if (time[1] == ':') {
			hours = time[0] - 48;
			minutes = (time[2] - 48) * 10 + time[3] - 48;
		} else {
			hours = ((time[0] - 48) * 10 + time[1] - 48) % 12;
			minutes = (time[3] - 48) * 10 + time[4] - 48;
		}

		double hourHandAngle = getHourHandAngle(hours, minutes);
		double minuteHandAngle = getMinuteHandAngle(minutes);
		double angleDifference = abs(hourHandAngle - minuteHandAngle);
		if (angleDifference <= 180.0) {
			cout << fixed << setprecision(1) << angleDifference << endl;
		} else {
			cout << fixed << setprecision(1) << 360.0 - angleDifference << endl;
		}
	}

	return 0;
}

inline void readTime(vector<char> &time) {
	char c = cin.get();

	while (c == '\n') {
		c = cin.get();
	}

	while (c != '\n' && c != EOF) {
		time.push_back(c);
		c = cin.get();
	}
}

inline double getMinuteHandAngle(int &minutes) {
	// static_cast<double>(minutes) / 60.0 * 360.0
	return static_cast<double>(minutes) * 6.0;
}

inline double getHourHandAngle(int &hours, int &minutes) {
	// (static_cast<double>(hours) + static_cast<double>(minutes) / 60.0) / 12.0 * 360
	return (static_cast<double>(hours) + static_cast<double>(minutes) / 60.0) * 30.0;
}
