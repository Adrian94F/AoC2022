//
// Created by luxoft on 05/12/22.
//

#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int day3() {
    ifstream input("./day3.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    auto priorities_sum = 0;
    string line;
    while (getline(input, line)) {
        auto mid = line.length() / 2;
        auto compartment1 = line.substr(0, mid);
        auto compartment2 = line.substr(mid, line.length());

        set<char> common;
        auto priority = 0;
        for (auto c1 : compartment1) {  // find shared items
            for (auto c2 : compartment2) {
                if (c1 == c2) {
                    common.insert(c1);
                }
            }
        }
        for (auto c : common) {  // calculate item's priority
            if (islower(c)) {
                priority += c - 'a' + 1;
            }
            else {
                priority += c - 'A' + 27;
            }
        }
        priorities_sum += priority;  // sum of priorities
    }
    cout << "Sum of priorities of shared items: " << priorities_sum << endl;
    input.close();
    return 0;
}
