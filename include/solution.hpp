#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "placement.hpp"
#include "trie.hpp"
#include "grid.hpp"

struct Anchor {
    size_t x;
    size_t y;
    size_t x_length;
    size_t y_length;
    const Trie *x_trie;
    const Trie *y_trie;

    bool operator<(const Anchor& other) const {
        if(x < other.x) return true;
        if(x > other.x) return false;
        return y < other.y;
    }
};

bool removeFromRack(std::string& rack, std::string& word, char c);
bool removeWildFromRack(std::string& rack, std::string& word, char c);

class SolutionBuilder
{
public:
    SolutionBuilder(const Trie &trie, const Grid &grid);
    std::set<Placement> solve(std::string rack);
protected:
    void calculateAnchors();
    void addAnchor(size_t x, size_t y);

    void leftPart(
        std::string rack,
        std::string word,
        const Trie &segment,
        const Anchor &anchor,
        bool horizontal,
        size_t limit);

    void extendRight(
        std::string rack,
        std::string word,
        const Trie &trie,
        const Anchor &anchor,
        bool horizontal,
        size_t x,
        size_t y,
        size_t limit);

    bool crossCheck(size_t x, size_t y, bool horizontal, char character);
    void legalMove(std::string letters, size_t x, size_t y, bool horizontal, const Anchor &anchor, size_t limit);
    int score(const Grid &grid, size_t x, size_t y, bool horizontal, bool recursive=true);
    bool nextSquare(size_t &x, size_t &y, bool horizontal);

    std::set<Placement> placements;
    std::set<Anchor> anchors;
    const Trie& trie;
    const Grid& grid;
};

#endif