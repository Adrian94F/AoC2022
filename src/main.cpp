//
// Created by luxoft on 05/12/22.
//
#include "day1.cpp"
#include "day2.cpp"
#include "day3.cpp"

int main() {
    auto functions = {
            day1,
            Day2::run,
            day3
    };
    /*for (auto f : functions) {
        f();
    }*/
    (*rbegin(functions))(); // run last possible day
}