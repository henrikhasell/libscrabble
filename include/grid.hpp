#ifndef GRID_HPP
#define GRID_HPP

#include <map>
#include <set>
#include <string>
#include "trie.hpp"

extern std::map<char, int> charScores;
extern Trie validWords;

class Grid
{
public:
    struct Tile
    {
        enum Type
        {
            Normal,
            DoubleLetter,
            DoubleWord,
            TripleLetter,
            TripleWord,
            Start
        };
        Tile();
        Type type;
        bool wild;
        bool cross_check;
        char value;
    };

    static Grid Large();
    static Grid Small();

    Grid(size_t w, size_t h);
    Grid(const Grid &grid);
    ~Grid();

    Tile *getTile(size_t x, size_t y) const;
    bool isAnchor(size_t x, size_t y) const;
    void insert(size_t x, size_t y, bool horizontal, const std::string &word);

    std::string fetch(size_t x, size_t y, bool horizontal) const;
    bool validate(const Trie &trie, std::string &message) const;
    int score(size_t x, size_t y, bool horizontal, bool recursive = true);

    const size_t w;
    const size_t h;
protected:
    bool validateWords(const Trie &trie, std::string &message, bool horizontal) const;
    bool validateWords(const Trie &trie, std::string &message) const;
    bool validateLattice(std::string &message) const;
private:
    Tile *tiles;
};

#endif
