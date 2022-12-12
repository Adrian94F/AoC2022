#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Vec2D {
    int x, y;
};

int tail_length;
vector<Vec2D> knots;
vector<Vec2D> visited;
vector<string> lines;

void checkIfNew(int tail) {
    for (int i = 0; i < visited.size(); i++) {
        Vec2D p = visited.at(i);
        if (knots[tail].x == p.x && knots[tail].y == p.y) return;
    }
    visited.push_back(knots[tail]);
}

void moveTail(Vec2D& head, int curKnot) {
    int xDis = head.x - knots[curKnot].x;
    int yDis = head.y - knots[curKnot].y;
    if ((abs(xDis) + abs(yDis) > 2)) {
        knots[curKnot].x += (xDis > 0 ? 1 : -1);
        knots[curKnot].y += (yDis > 0 ? 1 : -1);
    }
    else if (abs(xDis) > 1) {
        knots[curKnot].x += (xDis > 0 ? 1 : -1);
    }
    else if (abs(yDis) > 1) {
        knots[curKnot].y += (yDis > 0 ? 1 : -1);
    }
    else {
        return;
    }
    if (curKnot == tail_length - 1) {
        checkIfNew(tail_length - 1);
    }
    if(curKnot + 1 < tail_length) {
        moveTail(knots[curKnot], curKnot + 1);
    }
}

void calculate(int tail_l) {
    Vec2D head = {0, 0};
    tail_length = tail_l;
    knots = vector<Vec2D>(tail_length);
    visited.clear();
    visited.push_back(head);
    for (auto line : lines) {
        char dir = line.at(0);
        int dis = stoi(line.substr(2, line.length() - 2));
        for (int i = 0; i < dis; i++) {
            switch (dir) {
                case 'U':
                    head.y--;
                    break;
                case 'D':
                    head.y++;
                    break;
                case 'L':
                    head.x--;
                    break;
                case 'R':
                    head.x++;
                    break;
            }

            moveTail(head, 0);
        }
    }
    cout << "Unique spots for tail of length " << tail_length << ": " << visited.size() << endl;
}

int day9()
{
    ifstream input("./day9.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    string line;
    while (getline(input, line)) {
        lines.push_back(line);
    }

    calculate(1);
    calculate(9);
}