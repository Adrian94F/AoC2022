//
// Created by luxoft on 05/12/22.
//

#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <vector>

using namespace std;

int get_prio(char c) {
    if (islower(c)) {
        return c - 'a' + 1;
    }
    else {
        return c - 'A' + 27;
    }
}

int day3() {
    ifstream input("./day3.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    auto priorities_sum_1 = 0;
    auto priorities_sum_2 = 0;
    auto group_counter = 0;
    list<string> group = {"", "", ""};
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
            priority += get_prio(c);
        }
        priorities_sum_1 += priority;  // sum of priorities

        group.pop_front();  // remove 1st element
        group.push_back(line);
        if (group_counter % 3 == 0) {
            vector rucksacks (group.begin(), group.end());
            if (rucksacks[0].empty()) {
                continue;
            }
            auto it = group.begin();
            auto found = false;
            for (auto c0 : rucksacks[0]) {  // find shared items in 3 rucksacks
                for (auto c1 : rucksacks[1]) {
                    for (auto c2 : rucksacks[2]) {
                        if (c0 == c1 && c1 == c2) {
                            priorities_sum_2 += get_prio(c0);
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
        group_counter++;
    }
    cout << "Sum of priorities of shared items: " << priorities_sum_1 << endl;
    cout << "Sum of priorities of shared items in groups of 3: " << priorities_sum_2 << endl;
    input.close();
    return 0;
}
