#include "trie.hpp"
#include <fstream>
#include <iostream>

Trie::Trie(const std::string &string) : character(string[0]), valid(string.length() == 1)
{
    if(!valid)
    {
        insert(string.substr(1));
    }
}

Trie::Trie() : character('\0'), valid(false)
{

}

bool Trie::contains(const std::string &string) const
{
    const Trie* trie = find(string);
    return trie ? trie->valid : false;
}

const Trie *Trie::find(const std::string &string) const {
    auto iterator = children.find(tolower(string[0]));

    if(iterator != children.end())
    {
        const Trie &trie = *iterator;

        if(string.length() == 1)
        {
            return &trie;
        }

        return trie.find(string.substr(1));
    }

    return nullptr;
}


void Trie::insert(const std::string &string)
{
    auto iterator = children.find(string[0]);

    if(iterator == children.end())
    {
        children.insert(string);
    }
    else
    {
        Trie &trie = (Trie&)*iterator;

        if(string.length() == 1)
        {
            trie.valid = true;
        }
        else
        {
            trie.insert(string.substr(1));
        }
    }
}

bool Trie::operator< (const Trie &right) const
{
    return character < right.character;
}

bool Trie::operator> (const Trie &right) const
{
    return character > right.character;
}

bool Trie::operator<= (const Trie &right) const
{
    return character <= right.character;
}

bool Trie::operator>= (const Trie &right) const
{
    return character <= right.character;
}

bool Trie::operator== (const Trie &right) const
{
    return character == right.character;
}

bool Trie::operator!= (const Trie &right) const
{
    return character != right.character;
}

Trie::Trie(char character) : character(character) {}

Trie loadDictionary(const char path[])
{
    Trie trie;
    std::ifstream file;

    file.open(path);

    if(!file)
    {
        std::cerr << "Failed to open " << path << std::endl;
    }
    else
    {
        std::string word;
        while(file >> word)
        {
            for(char &i : word) i = tolower(i);
            trie.insert(word);
        }
    }

    return trie;
}