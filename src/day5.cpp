#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <iterator>

using namespace std;

int position_of_element_in_stack(int stack_number) {
    return 4 * stack_number - 3;
}


void print_stacks(vector<list<char>> stacks) {
    auto s_idx = 0;
    for (const auto& s : stacks) {
        cout << ++s_idx << ": ";
        for (auto c : s) {
            cout << c << ' ';
        }
        cout << endl;
    }
}

int day5() {
    ifstream input("./day5.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    string line;
    vector<string> stacks_description;
    vector<string> instructions;
    while (getline(input, line)) {
        if (line.empty()) {
            break;
        }
        stacks_description.push_back(line);
    }
    while (getline(input, line)) {
        instructions.push_back(line);
    }
    input.close();

    stringstream ss(stacks_description[stacks_description.size() - 1]);
    vector<string> stack_numbers((istream_iterator<string>(ss)), istream_iterator<string>());
    auto stacks = vector<list<char>>(stoi(*stack_numbers.rbegin()));

    auto s_idx = 1;
    for (auto& s : stacks) {
        auto pos = position_of_element_in_stack(s_idx++);
        for (auto l = stacks_description.begin(); l != stacks_description.end() - 1; ++l) {
            if (l->size() > pos) {
                auto c = (*l)[pos];
                if (c != ' ') {
                    s.push_back(c);
                }
            }
        }
    }
    auto stacks2 = stacks;
    print_stacks(stacks);

    for (const auto& l : instructions) {
        ss = stringstream(l);
        vector<std::string> words((istream_iterator<string> (ss)), istream_iterator<string>());

        auto quantity = stoi(words[1]);
        auto from = stoi(words[3]) - 1;
        auto to = stoi(words[5]) - 1;

        // part 1
        for (auto i = 0; i < quantity; i++) {
            auto c = *stacks[from].begin();
            stacks[from].pop_front();
            stacks[to].push_front(c);
        }

        // part 2
        vector<char> temp = {};
        for (auto i = 0; i < quantity; i++) {
            auto c = *stacks2[from].begin();
            stacks2[from].pop_front();
            temp.push_back(c);
        }
        for (auto c = temp.rbegin(); c != temp.rend(); ++c) {
            stacks2[to].push_front(*c);
        }
    }
    cout << "Message: ";
    for (const auto& s : stacks) {
        cout << *s.begin();
    }
    cout << endl << "Message2: ";
    for (const auto& s : stacks2) {
        cout << *s.begin();
    }
    cout << endl;

    return 0;
}