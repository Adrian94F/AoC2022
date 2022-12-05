#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class Day2 {
protected:
    static string figure(int value){
        switch (value) {
            case 0:
                return "rock";
            case 1:
                return "paper";
            case 2:
                return "scissors";
            default:
                return "ERROR";
        }
    }

    static string round_result(int value){
        switch (value) {
            case 0:
                return "loose";
            case 1:
                return "draw";
            case 2:
                return "win";
            default:
                return "ERROR";
        }
    }

    static int calculate1(int given, int played) {
        auto score = played + 1;
        if (given == played) {
            score += 3;
        } else if (played == given + 1 || played == given - 2) {
            score += 6;
        }
        return score;
    }

    static int calculate2(int given, int result) {
        auto score = 0;
        switch (result) {
            case 0:
                switch (given) {
                    case 0:  // scissors needed
                        score += 3;
                        break;
                    case 1:  // rock needed
                        score += 1;
                        break;
                    case 2:  // paper needed
                        score += 2;
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                score += 3;
                switch (given) {
                    case 0:  // rock needed
                        score += 1;
                        break;
                    case 1:  // paper needed
                        score += 2;
                        break;
                    case 2:  // scissors needed
                        score += 3;
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                score += 6;
                switch (given) {
                    case 0:  // paper needed
                        score += 2;
                        break;
                    case 1:  // scissors needed
                        score += 3;
                        break;
                    case 2:  // rock needed
                        score += 1;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        return score;
    }

public:
    static int run() {
        ifstream input("./day2.txt");
        if (!input.is_open()) {
            cout << "Unable to open file";
            return -1;
        }
        string line;
        auto total_score_part_1 = 0;
        auto total_score_part_2 = 0;
        while (getline(input, line)) {
            const auto given = line[0] - 'A';  // 0 - rock, 1 - paper, 2 - scissors
            auto played = line[2] - 'X';  // 0 - rock, 1 - paper, 2 - scissors
            auto score = calculate1(given, played);
            total_score_part_1 += score;

            cout << "Part1:\tscore: " << score << " \t" << figure(given) << " <-- " << figure(played) << endl;

            auto result = played; // 0 - loose, 1 - draw, 2 - win

            score = calculate2(given, result);
            auto need_to_play = (given + result - 1) % 3;
            total_score_part_2 += score;

            cout << "Part2:\tscore: " << score << " \t" << figure(given) << " <--need-to-"
                 << round_result(result) << "--- " << figure(need_to_play) << endl;

        }
        input.close();
        cout << "total score part 1: " << total_score_part_1 << endl;
        cout << "total score part 2: " << total_score_part_2 << endl;
        return 0;
    }

};