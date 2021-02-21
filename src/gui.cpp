#include "gui.hpp"
#include "gui_text.hpp"

SDL_Surface *renderGrid(const Grid &grid, const Cursor &cursor, SDL_Surface *fontmap) {
    SDL_Surface *destination = SDL_CreateRGBSurface(0, TILE_SIZE * grid.w, TILE_SIZE * grid.h, 24, 0xff0000, 0x00ff00, 0x0000ff, 0x00000000);
    SDL_Rect dstRect;

    for (size_t x = 0; x < grid.w; x++) {
        for (size_t y = 0; y < grid.h; y++) {
            const Grid::Tile *tile = grid.getTile(x, y);

            dstRect.x = (int)x * TILE_SIZE;
            dstRect.y = (int)y * TILE_SIZE;
            dstRect.w = TILE_SIZE;
            dstRect.h = TILE_SIZE;

            Uint32 colour;

            if (tile->value != ' ') {
                colour = 0xf0b432;
            } else {
                switch (tile->type) {
                    case Grid::Tile::Normal:
                        colour = 0xdee4ea;
                        break;
                    case Grid::Tile::DoubleWord:
                        colour = 0xb3554d;
                        break;
                    case Grid::Tile::DoubleLetter:
                        colour = 0x1181be;
                        break;
                    case Grid::Tile::TripleWord:
                        colour = 0xea9932;
                        break;
                    case Grid::Tile::TripleLetter:
                        colour = 0x6ea256;
                        break;
                    case Grid::Tile::Start:
                        colour = 0x78569a;
                        break;
                }
            }
            SDL_FillRect(destination, &dstRect, colour);
            if (tile->value != ' ') {
                renderCharacter(destination, fontmap, (int) x, (int) y, TILE_SIZE, TILE_SIZE, tile->value);
            }
        }
    }

    if(cursor.mode == Cursor::Board)
    {
        renderCharacter(
            destination, fontmap,
            (int)cursor.x,
            (int)cursor.y,
            TILE_SIZE,
            TILE_SIZE, 224);
    }

    return destination;
}
SDL_Surface *renderInput(
    const std::string &input,
    const Cursor &cursor,
    SDL_Surface *fontmap)
{
    SDL_Surface *destination = SDL_CreateRGBSurface(0, TILE_SIZE * 15, TILE_SIZE, 24, 0xff0000, 0x00ff00, 0x0000ff, 0x00000000);
    SDL_Rect dst_rect;

    dst_rect.x = 0;
    dst_rect.y = destination->h - TILE_SIZE;
    dst_rect.w = destination->w;
    dst_rect.h = TILE_SIZE;

    SDL_FillRect(destination, &dst_rect, 0x999999);

    int i;
    for(i = 0; i < input.length(); i++)
    {
        renderCharacter(destination, fontmap, i, dst_rect.y, TILE_SIZE, TILE_SIZE, input[i]);
    }
    if(cursor.mode == Cursor::Rack)
    {
        renderCharacter(destination, fontmap, i, 0, TILE_SIZE, TILE_SIZE, 224);
    }

    return destination;
}