#include <bits/stdc++.h>
#include <iostream>

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 6

using namespace std;

int X = 1;
int cycle = 0;
vector<int> cycle_numbers = {20, 60, 100, 140, 180, 220};
int strengths_sums = 0;

char screen[SCREEN_HEIGHT * SCREEN_WIDTH];

int signal_strength(int c) {
    return c * X;
}

void inc_cycle() {
    // PART 2
    int sprite_pos[] = {X - 1, X, X+1};
    for (auto i = 0; i < 3; i++) {
        if ((cycle % SCREEN_WIDTH) == sprite_pos[i]) {
            screen[cycle] = '#';
        }
    }

    cycle++;

    // PART 1
    auto cycle_to_check = min_element(cycle_numbers.begin(), cycle_numbers.end());
    if (cycle == *cycle_to_check) {
        auto strength = signal_strength(cycle);
        cycle_numbers.erase(cycle_to_check);
        strengths_sums += strength;
    }
}

int day10() {
    ifstream input("./day10.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    // clear screen for PART 2
    for (auto x = 0; x < SCREEN_WIDTH; x++) {
        for (auto y = 0; y < SCREEN_HEIGHT; y++) {
            screen[x + y * SCREEN_WIDTH] = ' ';
        }
    }

    string line;
    while (getline(input,line)) {
        auto ss = stringstream(line);
        vector<std::string> words((istream_iterator<string> (ss)), istream_iterator<string>());

        if (words[0] == "noop") {
            inc_cycle();
        } else if (words[0] == "addx") {
            inc_cycle();
            inc_cycle();
            X += stoi(words[1]);
        }
    }
    input.close();
    inc_cycle();

    // PART 1
    cout << "Sum of strengths: " << strengths_sums << endl;

    // PART 2
    auto pos = 0;
    for (auto y = 0; y < SCREEN_HEIGHT; y++) {
        for (auto x = 0; x < SCREEN_WIDTH; x++) {
            cout << screen[pos++];
        }
        cout << endl;
    }

    return 0;
}
