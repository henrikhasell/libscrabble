#include <gtest/gtest.h>
#include <fstream>
#include "trie.hpp"
#include "grid.hpp"
#include "solution.hpp"

struct WWFTest : testing::Test {
    WWFTest() {}
};

struct TrieTest : WWFTest {
    Trie trie;

    TrieTest() : WWFTest(), trie(loadDictionary("dictionary.txt")) {}
};

struct GridTest : WWFTest {
    Grid grid;
    Trie trie;
    std::string message;

    GridTest() : WWFTest(), grid(Grid::Large()), trie(loadDictionary("dictionary.txt")) {
        grid.insert(7, 7, true, "monkey");
        grid.insert(9, 5, false, "mokey");
        grid.insert(7, 8, false, "onkey");
        for(auto x = 0; x < grid.w; x++) {
            for(auto y = 0; y < grid.h; y++) {
                grid.getTile(x, y)->cross_check = false;
            }
        }
    }
};

struct SmallGridTest : WWFTest {
    Grid grid;

    SmallGridTest() : WWFTest(), grid(Grid::Small()) {
        grid.insert(1, 5, true, "skips");
        grid.insert(3, 3, false, "alzarin");
        grid.insert(2, 9, true, "q");
        grid.insert(1, 10, true, "sice");
        for(auto x = 0; x < grid.w; x++) {
            for(auto y = 0; y < grid.h; y++) {
                grid.getTile(x, y)->cross_check = false;
            }
        }
        for(auto y = 0; y < grid.h; y++) {
            for(auto x = 0; x < grid.w; x++) {
                printf("%c ", grid.getTile(x, y)->value);
            }
            putc('\n', stdout);
        }
    }
};

struct SolutionBuilderTest : GridTest {
    SolutionBuilder solutionBuilder;
    Trie trie;
    SolutionBuilderTest() :
        GridTest(),
        trie(loadDictionary("dictionary.txt")),
        solutionBuilder(trie, grid) {}
};

struct SmallSolutionBuilderTest : SmallGridTest {
    SolutionBuilder solutionBuilder;
    Trie trie;
    std::string message;

    SmallSolutionBuilderTest() :
        SmallGridTest(),
        trie(loadDictionary("dictionary.txt")),
        solutionBuilder(trie, grid) {}
};

TEST_F(TrieTest, TrieContainsTest)
{
    EXPECT_EQ(true, trie.contains("apple"));
    EXPECT_EQ(false, trie.contains("appl"));
    EXPECT_EQ(false, trie.contains("mispelt"));
    EXPECT_EQ(false, trie.contains("continuedd"));
}

TEST_F(GridTest, GridInsertAndFetchTest)
{
    grid.insert(10, 5, true, "onkey");
    EXPECT_EQ("monkey", grid.fetch(7, 7, true));
    EXPECT_EQ("monkey", grid.fetch(7, 7, false));
    EXPECT_EQ("monkey", grid.fetch(12, 7, true));
    EXPECT_EQ("monkey", grid.fetch(7, 12, false));
    EXPECT_EQ("", grid.fetch(13, 7, true));
    EXPECT_EQ("", grid.fetch(7, 13, false));
    EXPECT_EQ(true, grid.validate(trie, message));
}

TEST_F(SolutionBuilderTest, SolutionCorrect)
{
    std::set<Placement> placements = solutionBuilder.solve("monkey");
    const Placement& placement = *placements.rbegin();
    EXPECT_EQ(32, placement.score);
}

TEST_F(SmallSolutionBuilderTest, PlacementCorrect)
{
    std::set<Placement> placements = solutionBuilder.solve("jad");
    const Placement& placement = *placements.rbegin();
    const Placement expected = {
        .horizontal = false,
        .word = "jade",
        .x = 5,
        .y = 7,
        .score = 28
    };
    EXPECT_EQ(true, grid.validate(trie, message));
    EXPECT_EQ(expected.word, placement.word);
    EXPECT_EQ(expected.score, placement.score);
    EXPECT_EQ(expected.x, placement.x);
    EXPECT_EQ(expected.y, placement.y);
    EXPECT_EQ(expected.horizontal, placement.horizontal);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
