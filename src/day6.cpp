#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int day6() {
    ifstream input("./day6.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    string line;
    while (getline(input,line)) {
        const map<int, string> marker_types = {
                {4, "packet"},
                {14, "message"}
        };
        for (const auto& m : marker_types) {
            const auto marker_characters = m.first;
            for (auto i = 0; i < line.size() - marker_characters; i++) {
                set<char> marker;
                for (auto j = 0; j < marker_characters; j++) {
                    marker.insert(line[i + j]);
                }
                if (marker.size() == marker_characters) {
                    cout << "start of " << m.second << " marker: " << i + marker_characters << endl;
                    break;
                }
            }
        }
    }
    input.close();

    return 0;
}
