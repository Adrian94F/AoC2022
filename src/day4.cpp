#include <iostream>
#include <fstream>

using namespace std;

int day4() {
    ifstream input("./day4.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    auto containing_pairs = 0;
    auto overlapping_pairs = 0;
    string line;
    while (getline(input, line)) {
        string pair_delimiter = ",";
        string range_delimiter = "-";
        auto range1 = line.substr(0, line.find(pair_delimiter));
        auto range2 = line.substr(line.find(pair_delimiter) + pair_delimiter.length(), line.length());
        auto r1_delimiter = range1.find(range_delimiter);
        auto r2_delimiter = range2.find(range_delimiter);
        auto r1_0 = stoi(range1.substr(0, r1_delimiter));
        auto r1_1 = stoi(range1.substr(r1_delimiter + range_delimiter.length(), range1.length()));
        auto r2_0 = stoi(range2.substr(0, r2_delimiter));
        auto r2_1 = stoi(range2.substr(r2_delimiter + range_delimiter.length(), range2.length()));

        if ((r1_0 <= r2_0 and r1_1 >= r2_1) or (r1_0 >= r2_0 and r1_1 <= r2_1)) {
            containing_pairs++;
        }
        if (not(r1_0 > r2_1 or r1_1 < r2_0)) {
            overlapping_pairs++;
        }
    }
    input.close();

    cout << "Containing pairs: " << containing_pairs << endl;
    cout << "Overlapping pairs: " << overlapping_pairs << endl;
    return 0;
}