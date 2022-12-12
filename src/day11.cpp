#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Monkey {
    enum Operation {
        ADD,
        MUL,
        SQR
    };

    int id_;
    vector<int> items_;
    Operation operationType_;
    int operationArgument_;
    int divisibleBy_;
    int targetMonkeyIfTrue_;
    int targetMonkeyIfFalse_;
    int inspectedItems_ = 0;
};

ostream& operator<<(ostream& s, const Monkey& m) {
    s << "Monkey " << m.id_ << ": ";
    for (auto& i : m.items_) {
        s << i << " ";
    }
    return s;
}

int rounds = 20;

vector<Monkey> monkeys;

int readMonkeys() {
    ifstream input("./day11.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    string line;
    Monkey monke;
    while (getline(input,line)) {
        auto ss = stringstream(line);
        vector<std::string> words((istream_iterator<string> (ss)), istream_iterator<string>());
        if (not words.empty()) {
            if (words[0] == "Monkey") {
                monke.id_ = stoi(words[1]);
                cout << "Makin\' monke with id " << monke.id_ << endl;
            } else if (words[0] == "Starting") {
                cout << "\tMonke haz items: ";
                for (auto i = 2; i < words.size(); i++) {
                    auto val = stoi(words[i]);
                    monke.items_.push_back(val);
                    cout << val << " ";
                }
                cout << endl;
            } else if (words[0] == "Operation:") {
                if (words[4] == "+") {
                    monke.operationType_ = Monkey::ADD;
                    monke.operationArgument_ = stoi(words[5]);
                } else if (words[4] == "*") {
                    if (words[5] == "old") {
                        monke.operationType_ = Monkey::SQR;
                    } else {
                        monke.operationType_ = Monkey::MUL;
                        monke.operationArgument_ = stoi(words[5]);
                    }
                }
            } else if (words[0] == "Test:") {
                monke.divisibleBy_ = stoi(words[3]);
                cout << "\tMonke checks divisability by " << monke.divisibleBy_ << endl;
            } else if (words[0] == "If") {
                auto receiver = stoi(words[5]);
                cout << "\tMonke throws to " << receiver << " if ";
                if (words[1] == "true:") {
                    cout << "true\n";
                    monke.targetMonkeyIfTrue_ = receiver;
                } else {
                    cout << "false\n";
                    monke.targetMonkeyIfFalse_ = receiver;
                }
            }
        }
        else {
            cout << "Added monke to monkeys" << endl;
            monkeys.push_back(monke);
            monke = {};
        }

    }
    input.close();
    monkeys.push_back(monke);
    cout << "Added monke to monkeys" << endl << endl << endl;

    return 0;
}

int day11() {
    if (auto ret = readMonkeys()) {
        return ret;
    }

    while (rounds-->0) {
        for (auto& monke : monkeys) {
            cout << "Monkey " << monke.id_ << ":\n";
            for (auto& item : monke.items_) {
                cout << "  Monkey inspects an item with a worry level of " << item << ".\n    Worry level ";
                monke.inspectedItems_++;
                switch (monke.operationType_) {  // make operation
                    case Monkey::ADD:
                        item += monke.operationArgument_;
                        cout << "increases by " << monke.operationArgument_ << " to " << item << ".\n";
                        break;
                    case Monkey::MUL:
                        item *= monke.operationArgument_;
                        cout << "is multiplied by " << monke.operationArgument_ << " to " << item << ".\n";
                        break;
                    case Monkey::SQR:
                        item *= item;
                        cout << "is multiplied by itself to " << item << ".\n";
                        break;
                }

                item = item / 3;  // divide by 3
                cout << "    Monkey gets bored with item. Worry level is divided by 3 to " << item;

                auto divisible = item % monke.divisibleBy_ == 0;  // check if divisible
                int targetMonkey;
                cout << "    Current worry level is ";
                if (divisible) {
                    targetMonkey = monke.targetMonkeyIfTrue_;
                } else {
                    cout << "not ";
                    targetMonkey = monke.targetMonkeyIfFalse_;
                }
                cout << "divisible by " << monke.divisibleBy_ << ".\n    Item with worry level " << item <<
                        " is thrown to monkey " << targetMonkey << ".\n";
                monkeys[targetMonkey].items_.push_back(item);

            }
            monke.items_.clear();
        }

        multiset<int> inspectedItems;
        for (auto& monke : monkeys) {
            cout << monke << "\n\tinspected " << monke.inspectedItems_ << " items" << endl;
            inspectedItems.insert(monke.inspectedItems_);
        }
        inspectedItems.erase(inspectedItems.begin(), --(--inspectedItems.end()));
        auto levelOfMonkeyBusiness = 1;
        for (auto i : inspectedItems) {
            levelOfMonkeyBusiness *= i;
        }
        cout << "Level of monkeys business is: " << levelOfMonkeyBusiness << endl;


    }

    return 0;
}
