#include "grid.hpp"
#include <queue>

Grid::Tile::Tile() : value(' '), type(Tile::Normal)
{

}


Grid Grid::Large()
{
    Grid grid(15, 15);

    grid.getTile(3, 0)->type = Tile::TripleWord;
    grid.getTile(6, 0)->type = Tile::TripleLetter;
    grid.getTile(8, 0)->type = Tile::TripleLetter;
    grid.getTile(11, 0)->type = Tile::TripleWord;

    grid.getTile(2, 1)->type = Tile::DoubleLetter;
    grid.getTile(5, 1)->type = Tile::DoubleWord;
    grid.getTile(9, 1)->type = Tile::DoubleWord;
    grid.getTile(12, 1)->type = Tile::DoubleLetter;

    grid.getTile(1, 2)->type = Tile::DoubleLetter;
    grid.getTile(4, 2)->type = Tile::DoubleLetter;
    grid.getTile(10, 2)->type = Tile::DoubleLetter;
    grid.getTile(13, 2)->type = Tile::DoubleLetter;

    grid.getTile(0, 3)->type = Tile::TripleWord;
    grid.getTile(3, 3)->type = Tile::TripleLetter;
    grid.getTile(7, 3)->type = Tile::DoubleWord;
    grid.getTile(11, 3)->type = Tile::TripleLetter;
    grid.getTile(14, 3)->type = Tile::TripleWord;

    grid.getTile(2, 4)->type = Tile::DoubleLetter;
    grid.getTile(6, 4)->type = Tile::DoubleLetter;
    grid.getTile(8, 4)->type = Tile::DoubleLetter;
    grid.getTile(12, 4)->type = Tile::DoubleLetter;

    grid.getTile(1, 5)->type = Tile::DoubleWord;
    grid.getTile(5, 5)->type = Tile::TripleLetter;
    grid.getTile(9, 5)->type = Tile::TripleLetter;
    grid.getTile(13, 5)->type = Tile::DoubleWord;

    grid.getTile(0, 6)->type = Tile::TripleLetter;
    grid.getTile(4, 6)->type = Tile::DoubleLetter;
    grid.getTile(10, 6)->type = Tile::DoubleLetter;
    grid.getTile(14, 6)->type = Tile::TripleLetter;

    grid.getTile(3, 7)->type = Tile::DoubleWord;
    grid.getTile(7, 7)->type = Tile::Start;
    grid.getTile(11, 7)->type = Tile::DoubleWord;

    grid.getTile(0, 8)->type = Tile::TripleLetter;
    grid.getTile(4, 8)->type = Tile::DoubleLetter;
    grid.getTile(10, 8)->type = Tile::DoubleLetter;
    grid.getTile(14, 8)->type = Tile::TripleLetter;

    grid.getTile(1, 9)->type = Tile::DoubleWord;
    grid.getTile(5, 9)->type = Tile::TripleLetter;
    grid.getTile(9, 9)->type = Tile::TripleLetter;
    grid.getTile(13, 9)->type = Tile::DoubleWord;

    grid.getTile(2, 10)->type = Tile::DoubleLetter;
    grid.getTile(6, 10)->type = Tile::DoubleLetter;
    grid.getTile(8, 10)->type = Tile::DoubleLetter;
    grid.getTile(12, 10)->type = Tile::DoubleLetter;

    grid.getTile(0, 11)->type = Tile::TripleWord;
    grid.getTile(3, 11)->type = Tile::TripleLetter;
    grid.getTile(7, 11)->type = Tile::DoubleWord;
    grid.getTile(11, 11)->type = Tile::TripleLetter;
    grid.getTile(14, 11)->type = Tile::TripleWord;

    grid.getTile(1, 12)->type = Tile::DoubleLetter;
    grid.getTile(4, 12)->type = Tile::DoubleLetter;
    grid.getTile(10, 12)->type = Tile::DoubleLetter;
    grid.getTile(13, 12)->type = Tile::DoubleLetter;

    grid.getTile(2, 13)->type = Tile::DoubleLetter;
    grid.getTile(5, 13)->type = Tile::DoubleWord;
    grid.getTile(9, 13)->type = Tile::DoubleWord;
    grid.getTile(12, 13)->type = Tile::DoubleLetter;

    grid.getTile(3, 14)->type = Tile::TripleWord;
    grid.getTile(6, 14)->type = Tile::TripleLetter;
    grid.getTile(8, 14)->type = Tile::TripleLetter;
    grid.getTile(11, 14)->type = Tile::TripleWord;

    return grid;
}

Grid Grid::Small()
{
    Grid grid(11, 11);

    grid.getTile(0, 0)->type = Tile::TripleLetter;
    grid.getTile(2, 0)->type = Tile::TripleWord;
    grid.getTile(8, 0)->type = Tile::TripleWord;
    grid.getTile(10, 0)->type = Tile::TripleLetter;

    grid.getTile(1, 1)->type = Tile::DoubleWord;
    grid.getTile(5, 1)->type = Tile::DoubleWord;
    grid.getTile(9, 1)->type = Tile::DoubleWord;

    grid.getTile(0, 2)->type = Tile::TripleWord;
    grid.getTile(2, 2)->type = Tile::DoubleLetter;
    grid.getTile(4, 2)->type = Tile::DoubleLetter;
    grid.getTile(6, 2)->type = Tile::DoubleLetter;
    grid.getTile(8, 2)->type = Tile::DoubleLetter;
    grid.getTile(10, 2)->type = Tile::TripleWord;

    grid.getTile(3, 3)->type = Tile::TripleLetter;
    grid.getTile(7, 3)->type = Tile::TripleLetter;

    grid.getTile(2, 4)->type = Tile::DoubleLetter;
    grid.getTile(8, 4)->type = Tile::DoubleLetter;

    grid.getTile(1, 5)->type = Tile::DoubleWord;
    grid.getTile(5, 5)->type = Tile::Start;
    grid.getTile(9, 5)->type = Tile::DoubleWord;

    grid.getTile(2, 6)->type = Tile::DoubleLetter;
    grid.getTile(8, 6)->type = Tile::DoubleLetter;

    grid.getTile(3, 7)->type = Tile::TripleLetter;
    grid.getTile(7, 7)->type = Tile::TripleLetter;

    grid.getTile(0, 8)->type = Tile::TripleWord;
    grid.getTile(2, 8)->type = Tile::DoubleLetter;
    grid.getTile(4, 8)->type = Tile::DoubleLetter;
    grid.getTile(6, 8)->type = Tile::DoubleLetter;
    grid.getTile(8, 8)->type = Tile::DoubleLetter;
    grid.getTile(10, 8)->type = Tile::TripleWord;

    grid.getTile(1, 9)->type = Tile::DoubleWord;
    grid.getTile(5, 9)->type = Tile::DoubleWord;
    grid.getTile(9, 9)->type = Tile::DoubleWord;

    grid.getTile(0, 10)->type = Tile::TripleLetter;
    grid.getTile(2, 10)->type = Tile::TripleWord;
    grid.getTile(8, 10)->type = Tile::TripleWord;
    grid.getTile(10, 10)->type = Tile::TripleLetter;

    return grid;
}

Grid::Grid(size_t w, size_t h) : w(w), h(h)
{
    tiles = new Tile[w * h];
}

Grid::Grid(const Grid &grid) : Grid(grid.w, grid.h)
{
    for(size_t i = 0; i < w * h; i++)
    {
        tiles[i] = grid.tiles[i];
    }
}

Grid::~Grid()
{
    delete[] tiles;
}

Grid::Tile *Grid::getTile(size_t x, size_t y) const
{
    return tiles + x + w * y;
}


void Grid::insert(size_t x, size_t y, bool horizontal, const std::string &word)
{
    size_t *i;
    size_t i_max;

    if(horizontal)
    {
        i = &x;
        i_max = w;
    }
    else
    {
        i = &y;
        i_max = h;
    }

    size_t index = 0;

    while(*i < i_max && word.length() != index)
    {
        Tile *tile = getTile(x, y);

        if(tile->value == ' ')
        {
            const char new_value = word[index++];
            tile->value = (char)tolower(new_value);
            tile->wild = new_value < 'a';
            tile->cross_check = true;
        }

        i[0]++;
    }
}

std::string Grid::fetch(size_t x, size_t y, bool horizontal) const
{
    std::string result;

    size_t *i;
    size_t i_max;

    if(horizontal)
    {
        i = &x;
        i_max = w;
    }
    else
    {
        i = &y;
        i_max = h;
    }

    while(*i > 0)
    {
        if(getTile(x, y)->value != ' ')
        {
            i[0]--;
        }
        if(getTile(x, y)->value == ' ')
        {
            i[0]++;
            break;
        }
    }

    while(*i < i_max)
    {
        Tile *tile = getTile(x, y);

        if(tile->value == ' ')
        {
            break;
        }
        result += tile->value;
        i[0]++;
    }

    return result;
}

bool Grid::validateWords(const Trie &trie, std::string &message, bool horizontal) const
{
    size_t i;
    size_t j;

    size_t i_max;
    size_t j_max;

    size_t *x;
    size_t *y;

    if(horizontal)
    {
        i_max = h;
        j_max = w;

        x = &j;
        y = &i;
    }
    else
    {
        i_max = w;
        j_max = h;

        x = &i;
        y = &j;
    }

    std::string word;

    for(i = 0; i < i_max; i++)
    {
        for(j = 0; j < j_max; j++)
        {
            Tile *tile = getTile(*x, *y);

            if(tile->value != ' ')
            {
                word += tile->value;
            }
            if(tile->value == ' ' || j == j_max - 1)
            {
                if(word.length() > 1)
                {
                    for(char &i : word)
                    {
                        i = tolower(i);
                    }
                    if(!trie.contains(word))
                    {
                        message = "Invalid word: " + word;
                        return false;
                    }
                }
                word.clear();
            }
        }
    }

    return true;
}

bool Grid::validateWords(const Trie &trie, std::string &message) const
{
    return validateWords(trie, message, true) && validateWords(trie, message, false);
}

bool Grid::validateLattice(std::string &message) const
{
    Grid copy = *this;

    std::queue<std::tuple<size_t, size_t>> open_set;
    open_set.emplace(w / 2, h / 2);

    while(!open_set.empty())
    {
        std::tuple<size_t, size_t> &head =
            open_set.front();

        const size_t x = std::get<0>(head);
        const size_t y = std::get<1>(head);

        Tile *tile = copy.getTile(x, y);

        if(tile->value != ' ')
        {

            if(x > 0)
            {
                open_set.emplace(x - 1, y);
            }
            if(y > 0)
            {
                open_set.emplace(x, y - 1);
            }
            if(x < w - 1)
            {
                open_set.emplace(x + 1, y);
            }
            if(y < h  - 1)
            {
                open_set.emplace(x, y + 1);
            }

            tile->value = ' ';
        }

        open_set.pop();
    }

    for(size_t i = 0; i < copy.w * copy.h; i++)
    {
        if(copy.tiles[i].value != ' ')
        {
            message = "Invalid lattice.";
            return false;
        }
    }

    return true;
}

bool Grid::validate(const Trie &trie, std::string &message) const
{
    bool result = validateLattice(message) && validateWords(trie, message);

    if(result)
    {
        message = "Validation successful.";
    }

    return result;
}

bool Grid::isAnchor(size_t x, size_t y) const {
    if(getTile(x, y)->value != ' ') {
        return false;
    }

    return (x > 0 && getTile(x - 1, y)->value != ' ') ||
           (y > 0 && getTile(x, y - 1)->value != ' ') ||
           (x < w - 1 && getTile(x + 1, y)->value != ' ') ||
           (y < h - 1 && getTile(x, y + 1)->value != ' ');
}
