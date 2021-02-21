#ifndef WORDS_WITH_FRIENDS_GUI_HPP
#define WORDS_WITH_FRIENDS_GUI_HPP

#ifndef GRID_OFFSET
#define GRID_OFFSET 16
#endif

#ifndef TILE_SIZE
#define TILE_SIZE 20
#endif

#include <SDL2/SDL.h>
#include "grid.hpp"

struct Cursor {
    enum Mode {Board, Rack} mode;
    size_t x;
    size_t y;
};

SDL_Surface *renderGrid(const Grid &grid, const Cursor &cursor, SDL_Surface *fontmap);
SDL_Surface *renderInput(const std::string &input, const Cursor &cursor, SDL_Surface *fontmap);

#endif
