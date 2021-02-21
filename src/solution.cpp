#include <fstream>
#include "solution.hpp"

SolutionBuilder::SolutionBuilder(const Trie& trie, const Grid& grid) : trie(trie), grid(grid) {}

std::set<Placement> SolutionBuilder::solve(std::string rack) {
    placements.clear();
    calculateAnchors();

    for(const Anchor& anchor : anchors) {
        const Trie& x_trie = anchor.x_trie ? *anchor.x_trie : trie;
        const Trie& y_trie = anchor.y_trie ? *anchor.y_trie : trie;

        for(const Trie& child : x_trie.children) {
            std::string _rack = rack;
            std::string _word;

            if(!removeFromRack(_rack, _word, child.character)) {
                continue;
            }

            leftPart(_rack, _word, child, anchor, true, anchor.x_length);
        }

        for(const Trie& child : y_trie.children) {
            std::string _rack = rack;
            std::string _word;

            if(!removeFromRack(_rack, _word, child.character)) {
                continue;
            }

            leftPart(_rack, _word, child, anchor, false, anchor.y_length);
        }
    }

    return placements;
}

void SolutionBuilder::calculateAnchors() {
    anchors.clear();
    for(size_t x = 0; x < grid.w; x++) {
        for(size_t y = 0; y < grid.h; y++) {
            if(grid.isAnchor(x, y)) {
                addAnchor(x, y);
            }
        }
    }
    if(anchors.size() == 0) {
        addAnchor(grid.w / 2, grid.h / 2);
    }
}

void SolutionBuilder::addAnchor(size_t x, size_t y) {
    Anchor anchor;

    anchor.x = x;
    anchor.y = y;

    anchor.x_length = 0;
    anchor.y_length = 0;

    while(x-- > 0) {
        if(grid.getTile(x, y)->value != ' ' || grid.isAnchor(x, y)) {
            break;
        }
        anchor.x_length++;
    }

    x = anchor.x;

    while(y-- > 0) {
        if(grid.getTile(x, y)->value != ' ' || grid.isAnchor(x, y)) {
            break;
        }
        anchor.y_length++;
    }

    if(anchor.x_length == 0 && anchor.x > 0) {
        const std::string word = grid.fetch(anchor.x - 1, anchor.y, true);
        anchor.x_trie = trie.find(word);
    } else {
        anchor.x_trie = nullptr;
    }

    if(anchor.y_length == 0 && anchor.y > 0) {
        const std::string word = grid.fetch(anchor.x, anchor.y - 1, false);
        anchor.y_trie = trie.find(word);
    } else {
        anchor.y_trie = nullptr;
    }

    anchors.insert(anchor);
}

int SolutionBuilder::score(const Grid &grid, size_t x, size_t y, bool horizontal, bool recursive)
{
    std::map<char, int> charScores;
    charScores['A'] = 1;
    charScores['B'] = 4;
    charScores['C'] = 4;
    charScores['D'] = 2;
    charScores['E'] = 1;
    charScores['F'] = 4;
    charScores['G'] = 3;
    charScores['H'] = 3;
    charScores['I'] = 1;
    charScores['J'] = 10;
    charScores['K'] = 5;
    charScores['L'] = 2;
    charScores['M'] = 4;
    charScores['N'] = 2;
    charScores['O'] = 1;
    charScores['P'] = 4;
    charScores['Q'] = 10;
    charScores['R'] = 1;
    charScores['S'] = 1;
    charScores['T'] = 1;
    charScores['U'] = 2;
    charScores['V'] = 5;
    charScores['W'] = 4;
    charScores['X'] = 8;
    charScores['Y'] = 3;
    charScores['Z'] = 10;

    int word_score = 0, adjacent_score = 0;

    size_t *i;
    size_t i_max;

    if(horizontal)
    {
        i = &x;
        i_max = grid.w;
    }
    else
    {
        i = &y;
        i_max = grid.h;
    }

    while(*i > 0)
    {
        i[0]--;

        Grid::Tile *tile = grid.getTile(x, y);

        if(tile->value == ' ')
        {
            i[0]++;
            break;
        }
    }

    int word_multiplier = 1;
    int tile_count = 0, new_tile_count = 0;
    bool cross_check = false;

    while(*i < i_max)
    {
        const Grid::Tile *tile = grid.getTile(x, y);

        if(tile->value == ' ')
        {
            break;
        }

        int tile_multiplier = 1;

        if(tile->cross_check)
        {
            switch(tile->type)
            {
                case Grid::Tile::DoubleLetter:
                    tile_multiplier = 2; break;
                case Grid::Tile::TripleLetter:
                    tile_multiplier = 3; break;
                case Grid::Tile::DoubleWord:
                    word_multiplier *= 2; break;
                case Grid::Tile::TripleWord:
                    word_multiplier *= 3; break;
            }

            if(recursive)
            {
                adjacent_score += score(grid, x, y, !horizontal, false);
            }

            cross_check = true;
            new_tile_count++;
        }

        if(!tile->wild)
        {
            word_score += tile_multiplier * charScores[toupper(tile->value)];
        }

        tile_count++;
        i[0]++;
    }

    if(cross_check && tile_count > 1)
    {
        word_score *= word_multiplier;
        word_score += adjacent_score;

        if(new_tile_count >= 7)
        {
            word_score += 35;
        }

        return word_score;
    }

    return 0;
}

void SolutionBuilder::leftPart(
        std::string rack,
        std::string word,
        const Trie &segment,
        const Anchor &anchor,
        bool horizontal,
        size_t limit)
{
    if(crossCheck(anchor.x, anchor.y, horizontal, segment.character)) {
        extendRight(rack, word, segment, anchor, horizontal, anchor.x, anchor.y, limit);
    }
    if(limit > 0) {
        for(const Trie &child : segment.children) {
            std::string _rack = rack;
            std::string _word = word;
            if(!removeFromRack(_rack, _word, child.character)) {
                continue;
            }
            leftPart(_rack, _word, child, anchor, horizontal, limit - 1);
        }
    }
}

void SolutionBuilder::extendRight(
        std::string rack,
        std::string word,
        const Trie &trie,
        const Anchor &anchor,
        bool horizontal,
        size_t x,
        size_t y,
        size_t limit)
{
    const bool edge = !nextSquare(x, y, horizontal);
    char tile_value = grid.getTile(x, y)->value;

    if(tile_value == ' ' || edge) {
        if(trie.valid) {
            legalMove(word, anchor.x, anchor.y, horizontal, anchor, limit);
        }
        if(edge) {
            return;
        }
        for(const Trie &child : trie.children) {
            std::string _rack = rack;
            std::string _word = word;
            if(!removeFromRack(_rack, _word, child.character)) {
                continue;
            }
            if(crossCheck(x, y, horizontal, child.character)) {
                extendRight(_rack, _word, child, anchor, horizontal, x, y, limit);
            }
        }
    }
    else
    {
        auto trieContinuation = trie.children.find(tile_value);

        if(trieContinuation != trie.children.end()) {
            extendRight(rack, word, *trieContinuation, anchor, horizontal, x, y, limit);
        }
    }
}

bool SolutionBuilder::nextSquare(size_t &x, size_t &y, bool horizontal) {
    if(horizontal) {
        if(x >= grid.w - 1) {
            return false;
        }
        x++;
    }

    else {
        if(y >= grid.h - 1) {
            return false;
        }
        y++;
    }
    return true;
}

bool SolutionBuilder::crossCheck(size_t x, size_t y, bool horizontal, char character) {
    Grid gridCopy = grid;
    gridCopy.getTile(x, y)->value = character;
    const std::string crossWord = gridCopy.fetch(x, y, !horizontal);
    return crossWord.length() == 1 || trie.contains(crossWord);
}

void SolutionBuilder::legalMove(std::string letters, size_t x, size_t y, bool horizontal, const Anchor &anchor, size_t limit) {
    if(horizontal) {
    x -= anchor.x_length - limit;
    }
    else {
    y -= anchor.y_length - limit;
    }

    Grid gridCopy = grid;
    gridCopy.insert(x, y, horizontal, letters);
    int score = this->score(gridCopy, x, y, horizontal);

    Placement placement;
    placement.x = x;
    placement.y = y;
    placement.horizontal = horizontal;
    placement.letters = letters;
    placement.word = gridCopy.fetch(x, y, horizontal);
    placement.score = score;

    placements.insert(placement);
}

bool removeFromRack(std::string& rack, std::string& word, char c)
{
    auto position = rack.find(c);
    if (position == std::string::npos) {
        return removeWildFromRack(rack, word, c);
    }
    rack.erase(position, 1);
    word += tolower(c);
    return true;
}

bool removeWildFromRack(std::string& rack, std::string& word, char c)
{
    auto position = rack.find('*');
    if (position == std::string::npos) {
        return false;
    }
    rack.erase(position, 1);
    word += toupper(c);
    return true;
}