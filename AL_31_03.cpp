#include <cstdio>
#include <vector>

using namespace std;

class Record {
	public:
		char name[2] = {};
		char lastName[11] = {};
		char age[3] = {};
		char pesel[12] = {};

		void print() {
			printf("%s. %s %s %s", name, lastName, age, pesel);
		}
};

inline void countingSort(vector<Record*>&records, char* (*key)(Record*), int index, bool ascending);
inline void radixSort(vector<Record*>&records, char* (*key)(Record*), int keyLength, bool ascending);
inline Record* decipherStringRecord(vector<char>&record);
inline int getStringRecord(vector<char>&record);
inline char* getLastName(Record* record);
inline char* getPesel(Record* record);
inline char* getName(Record* record);

int main() {

	int numberOfRecords;
	vector<Record*>records;
	vector<char>record;
	record.reserve(25);

	while (getStringRecord(record) != EOF) {
		Record* newRecord = decipherStringRecord(record);
		records.push_back(newRecord);
	}

	radixSort(records, getPesel, 11, false);
	radixSort(records, getName, 1, true);
	// radixSort(records, [](Record* record)->char* { return record->lastName; }, 10, true);
	radixSort(records, getLastName, 10, true);

	numberOfRecords = records.size();

	for (int i = 0; i < numberOfRecords; ++i) {
		records[i]->print();
		putchar('\n');
	}

	// Delete vector<Record*>records
	for (int i = 0; i < numberOfRecords; ++i) {
		delete records[i];
	}

	records.clear();

	return 0;
}

inline char* getName(Record* record) {
	return record->name;
}

inline char* getPesel(Record* record) {
	return record->pesel;
}

inline char* getLastName(Record* record) {
	return record->lastName;
}

inline void countingSort(vector<Record*>&records, char* (*key)(Record*), int index, bool ascending) {
	vector<vector<Record*> >array;
	array.resize(126);

	for (int i = 0, numberOfRecords = records.size(); i < numberOfRecords; ++i) {
		array[(int)key(records[i])[index]].push_back(records[i]);
	}

	if (ascending) {
		for (int i = 0, recordsIter = 0; i < 126; ++i) {
			int numberOfRecords = array[i].size();
			for (int j = 0; j < numberOfRecords; ++j) {
				records[recordsIter] = array[i][j];
				recordsIter++;
			}
		}
	} else {
		for (int i = 99, recordsIter = 0; i >= 0; --i) {
			for (int j = 0, numberOfRecords = array[i].size(); j < numberOfRecords; ++j) {
				records[recordsIter] = array[i][j];
				recordsIter++;
			}
		}
	}
}

inline void radixSort(vector<Record*>&records, char* (*key)(Record*), int keyLength, bool ascending) {
	for (int i = keyLength - 1; i >= 0; --i) {
		countingSort(records, key, i, ascending);
	}
}

inline Record* decipherStringRecord(vector<char>&record) {
	Record* userRecord = new Record();
	int recordLength = record.size();

	for (int i = 0; i < recordLength; ++i) {
		if (record[i] == '.') {
			userRecord->name[0] = record[i - 1];
			record.erase(next(record.begin(), i - 1), next(record.begin(), i + 1));
			recordLength -= 2;
			break;
		}
	}

	for (int i = 0, j; i < recordLength; ++i) {
		if ((int)record[i] > 57) {
			for (j = i; j < recordLength && (int)record[j] > 57; ++j) {
				userRecord->lastName[j - i] = record[j];
			}
			record.erase(next(record.begin(), i), next(record.begin(), j));
			break;
		}
	}

	if (record[0] == '1' || record[0] == '2' || record[0] == '3') {
		for (int i = 2; i < 13; ++i) {
			userRecord->pesel[i - 2] = record[i];
		}
		userRecord->age[0] = record[0];
		userRecord->age[1] = record[1];
	} else {
		for (int i = 0; i < 11; ++i) {
			userRecord->pesel[i] = record[i];
		}
		userRecord->age[0] = record[11];
		userRecord->age[1] = record[12];
	}

	return userRecord;
}

inline int getStringRecord(vector<char>&record) {
	char c = getchar();
	
	record.clear();

	while (c == '\n') {
		c = getchar();
	}

	if (c != EOF) {
		while (c != '\n' && c != EOF) {
			record.push_back(c);
			c = getchar();
		}
	} else {
		return EOF;
	}

	return 0;
}
