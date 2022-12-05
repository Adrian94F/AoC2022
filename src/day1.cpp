#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> top_3_elves = {0, 0, 0};
auto calories = 0;

void check_calories() {
    auto min_value = min_element(top_3_elves.begin(), top_3_elves.end());
    if (calories > *min_value) {
        top_3_elves.erase(min_value);
        top_3_elves.push_back(calories);
    }
}

int day1() {
    ifstream input("./day1.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    string line;
    while (getline(input,line)) {
        if (line.empty()) {
            check_calories();
            calories = 0;
        }
        else {
            calories += stoi(line);
        }
    }
    check_calories();
    input.close();

    auto max = *max_element(top_3_elves.begin(), top_3_elves.end());
    auto sum = accumulate(top_3_elves.begin(), top_3_elves.end(), 0);

    cout << "Max calories sum: " << max << endl;
    cout << "Top " << top_3_elves.size() << " elves calories sum: " << sum << endl;

    return 0;
}
