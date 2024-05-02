#ifndef PLACEMENT_HPP
#define PLACEMENT_HPP

struct Placement
{
    bool horizontal;
    std::string letters;
    std::string word;
    size_t x;
    size_t y;
    int score;

    bool operator<(const Placement& other) const {
        if (score != other.score) return score < other.score;
        if (word != other.word) return word < other.word;
        if (x != other.x) return score < other.x;
        if (y != other.y) return score < other.y;
        return horizontal < other.horizontal;
    }
};

#endif