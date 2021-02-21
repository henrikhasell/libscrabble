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
        if(score < other.score) return true;
        if(score > other.score) return false;
        if(word < other.word) return true;
        if(word > other.word) return false;
        if(x < other.x) return true;
        if(x > other.x) return false;
        if(y < other.y) return true;
        if(y > other.y) return false;
        return horizontal < other.horizontal;
    }
};

#endif