#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


int main() {
    ifstream input("./day1.txt");

    if (input.is_open()) {
        string line;
        vector<int> elves;
        auto calories = 0;

        while ( getline (input,line) ) {
            if (line.empty()) {
                elves.push_back(calories);
                calories = 0;
            }
            else {
                calories += stoi(line);
            }
        }
        elves.push_back(calories);
        input.close();

        sort(elves.begin(), elves.end(), greater<>());

        cout << "Max calories sum: " << elves[0] << endl;
        cout << "Top 3 elves calories sum: " << accumulate(elves.begin(), elves.begin()+3, 0) << endl;
    }
    else {
        cout << "Unable to open file";
    }
    return 0;
}
