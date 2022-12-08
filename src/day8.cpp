#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int day8() {
    ifstream input("./day8.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    vector<vector<int>> trees;

    string line;
    while (getline(input,line)) {
        vector<int> row;
        for (auto c : line) {
            row.push_back(c - '0');
        }
        trees.push_back(row);
    }
    input.close();

    auto area_width = trees.begin()->size();
    auto area_height = trees.size();

    // PART 1
    auto visible_trees = 2 * area_width + 2 * area_height - 4;
    for (auto row = 1; row < area_height - 1; row++) {
        for (auto col = 1; col < area_width - 1; col++) {
            auto tree = trees[row][col];
            array<bool, 4> visible{true, true, true, true};
            auto sub_row = 0;
            while (visible[0] && sub_row < row) {
                if (trees[sub_row][col] >= tree) {
                    visible[0] = false;
                }
                sub_row++;
            }
            sub_row = area_height - 1;
            while (visible[1] && sub_row > row) {
                if (trees[sub_row][col] >= tree) {
                    visible[1] = false;
                }
                sub_row--;
            }
            auto sub_col = 0;
            while (visible[2] && sub_col < col) {
                if (trees[row][sub_col] >= tree) {
                    visible[2] = false;
                }
                sub_col++;
            }
            sub_col = area_width - 1;
            while (visible[3] && sub_col > col) {
                if (trees[row][sub_col] >= tree) {
                    visible[3] = false;
                }
                sub_col--;
            }
            std::unordered_set<int> v(begin(visible), end(visible));
            if (v.contains(true)) {
                visible_trees++;
            }
        }
    }
    cout << "Visible trees: " << visible_trees << endl;

    // PART 2
    auto highest_scenic_score = 0;
    for (auto row = 1; row < area_height - 1; row++) {  // ignore 1st and last row
        for (auto col = 1; col < area_width - 1; col++) {  // and column because of 0 factor
            auto tree = trees[row][col];
            auto top = 0;
            auto bottom = 0;
            auto left = 0;
            auto right = 0;
            {
                auto sub_row = row - 1;
                while (sub_row >= 0) {  // check top
                    top++;
                    if (trees[sub_row][col] >= tree) {
                        break;
                    }
                    sub_row--;
                }
                sub_row = row + 1;
                while (sub_row < area_height) {  // check bottom
                    bottom++;
                    if (trees[sub_row][col] >= tree) {
                        break;
                    }
                    sub_row++;
                }
            }
            {
                auto sub_col = col - 1;
                while (sub_col >= 0) {
                    left++;
                    if (trees[row][sub_col] >= tree) {  // check left
                        break;
                    }
                    sub_col--;
                }
                sub_col = col + 1;
                while (sub_col < area_width) {
                    right++;
                    if (trees[row][sub_col] >= tree) {  // check right
                        break;
                    }
                    sub_col++;
                }
            }
            auto scenic_score = top * bottom * left * right;
            if (scenic_score > highest_scenic_score) {
                highest_scenic_score = scenic_score;
            }
        }
    }

    cout << "Highest scenic score: " << highest_scenic_score << endl;

    return 0;
}
