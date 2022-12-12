#include "day1.cpp"
#include "day2.cpp"
#include "day3.cpp"
#include "day4.cpp"
#include "day5.cpp"
#include "day6.cpp"
#include "day7.cpp"
#include "day8.cpp"
#include "day9.cpp"
#include "day10.cpp"

#define LAST_ONLY true

int main() {
    auto functions = {
            day1,
            Day2::run,
            day3,
            day4,
            day5,
            day6,
            day7,
            day8,
            day9,
            day10
    };

#if LAST_ONLY
    (*rbegin(functions))(); // run last possible day
#else
    auto idx = 1;
    for (auto f : functions) {
        cout << endl << "Day " << idx++ << endl;
        f();
    }
#endif

    return 0;
}