#ifndef TRIE_HPP
#define TRIE_HPP

#include <set>
#include <string>

class Trie;
class SolutionBuilder;

class Trie
{
    friend class SolutionBuilder;
public:
    Trie(const std::string &string);
    Trie();

    bool operator< (const Trie &right) const;
    bool operator> (const Trie &right) const;
    bool operator<= (const Trie &right) const;
    bool operator>= (const Trie &right) const;
    bool operator== (const Trie &right) const;
    bool operator!= (const Trie &right) const;

    const Trie* find(const std::string &string) const;
    bool contains(const std::string &string) const;
    void insert(const std::string &string);
protected:
    std::set<Trie> children;
    char character;
    bool valid;
private:
    Trie(char character);
};

Trie loadDictionary(const char path[]);

#endif