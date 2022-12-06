#include <gtest/gtest.h>
#include "../src/day2.cpp"

#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define LOOSE 0
#define DRAW 1
#define WIN 2

struct {
    int given;
    int played;
    int score;
} typedef p1;

struct {
    int given;
    int result;
    int score;
} typedef p2;

class Day2Part1Fixture : public Day2, public ::testing::TestWithParam<p1> {
};

class Day2Part2Fixture : public Day2, public ::testing::TestWithParam<p2> {
};

TEST_P(Day2Part1Fixture, ScoreIsCountedCorrectly) {
    auto calculated_score = calculate1(GetParam().given, GetParam().played);
    ASSERT_EQ(calculated_score, GetParam().score);
}

TEST_P(Day2Part2Fixture, ScoreIsCountedCorrectly) {
    auto calculated_score = calculate2(GetParam().given, GetParam().result);
    ASSERT_EQ(calculated_score, GetParam().score);
}

INSTANTIATE_TEST_CASE_P(
        Day2Tests,
        Day2Part1Fixture,
        ::testing::Values(
                p1{ROCK,     ROCK,     4},
                p1{PAPER,    PAPER,    5},
                p1{SCISSORS, SCISSORS, 6},
                p1{ROCK,     PAPER,    8},
                p1{PAPER,    SCISSORS, 9},
                p1{SCISSORS, ROCK,     7},
                p1{ROCK,     SCISSORS, 3},
                p1{PAPER,    ROCK,     1},
                p1{SCISSORS, PAPER,    2}
        ));

INSTANTIATE_TEST_CASE_P(
        Day2Tests,
        Day2Part2Fixture,
        ::testing::Values(
                p2{ROCK, LOOSE, 3},
                p2{ROCK, DRAW, 4},
                p2{PAPER, LOOSE, 1}
        ));