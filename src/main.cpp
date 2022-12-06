#include "day1.cpp"
#include "day2.cpp"
#include "day3.cpp"
#include "day4.cpp"
#include "day5.cpp"
#include "day6.cpp"

int main() {
    auto functions = {
            day1,
            Day2::run,
            day3,
            day4,
            day5,
            day6
    };
    /*for (auto f : functions) {
        f();
    }*/
    (*rbegin(functions))(); // run last possible day
}