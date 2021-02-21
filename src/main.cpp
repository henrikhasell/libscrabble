#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "grid.hpp"
#include "gui.hpp"
#include "gui_text.hpp"
#include "solution.hpp"
#include "trie.hpp"

#define TILE_SIZE 20
#define GLYPH_W 8
#define GLYPH_H 8
#define GRID_SIZE_X 15
#define GRID_SIZE_Y 15


int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        SDL_Window *window = SDL_CreateWindow(
            "Word Game",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            TILE_SIZE * GRID_SIZE_X,
            TILE_SIZE * (GRID_SIZE_Y + 1) + 16,
            0);

        if(window)
        {

            bool small = false;

            for(int i = 0; i < argc; i++)
            {
                if(strcmp(argv[i], "--small") == 0)
                {
                    small = true;
                    break;
                }
            }

            Grid grid = small ? Grid::Small() : Grid::Large();
            const Trie validWords = loadDictionary("dictionary.txt");
            SolutionBuilder solutionBuilder(validWords, grid);
            std::string input;
            std::string validationMessage;
            bool validationResult = true;

            SDL_Surface *windowSurface = SDL_GetWindowSurface(window);
            SDL_Surface *fontMap = SDL_LoadBMP("Text.bmp");
            SDL_SetColorKey(fontMap, SDL_TRUE, 0x000000);

            bool finished = false;
            Cursor cursor = {
                .mode = Cursor::Board,
                .x = 0,
                .y = 0
            };

            while(!finished)
            {
                SDL_Event e;
                while(SDL_WaitEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        finished = true;
                        break;
                    }
                    else if(e.type == SDL_WINDOWEVENT)
                    {
                        if(e.window.event == SDL_WINDOWEVENT_RESIZED)
                        {
                            windowSurface = SDL_GetWindowSurface(window);
                        }
                    }
                    else if(e.type == SDL_TEXTINPUT)
                    {
                        if(cursor.mode == Cursor::Board)
                        {
                            Grid::Tile *tile = grid.getTile(cursor.x, cursor.y);
                            tile->value = e.text.text[0];
                            tile->cross_check = false;
			                tile->wild = false;
                            validationResult = grid.validate(validWords, validationMessage);
                        }
                        else if(input.length() < 7)
                        {
                            input += e.text.text;
                        }
                    }
                    else if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if(e.button.windowID && e.button.button == SDL_BUTTON_LEFT)
                        {
                            size_t xCoord = e.button.x / TILE_SIZE;
                            size_t yCoord = (e.button.y - GRID_OFFSET) / TILE_SIZE;

                            if(yCoord >= grid.h)
                            {
                                cursor.mode = Cursor::Rack;
                            }
                            else
                            {
                                cursor.mode = Cursor::Board;
                            }

                            cursor.x = std::min(grid.w - 1, xCoord);
                            cursor.y = std::min(grid.h - 1, yCoord);
                        }
                    }
                    else if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            if(cursor.mode == Cursor::Board)
                            {
                                if(cursor.y > 0)
                                {
                                    cursor.y--;
                                }
                            }
                            else
                            {
                                cursor.mode = Cursor::Board;
                            }
                            break;
                        case SDLK_DOWN:
                            if(cursor.mode == Cursor::Board)
                            {
                                if(cursor.y < grid.h - 1)
                                {
                                    cursor.y++;
                                }
                                else
                                {
                                    cursor.mode = Cursor::Rack;
                                }
                            }
                            break;
                        case SDLK_LEFT:
                            if(cursor.x > 0)
                            {
                                cursor.x--;
                            }
                            break;
                        case SDLK_RIGHT:
                            if(cursor.x < grid.w - 1)
                            {
                                cursor.x++;
                            }
                            break;
                        case SDLK_RETURN:
                            if(cursor.mode == Cursor::Board)
                            {
                                validationResult = grid.validate(validWords, validationMessage);
                            }
                            else
                            {
                                for(size_t x = 0; x < grid.w; x++)
                                {
                                    for(size_t y = 0; y < grid.h; y++)
                                    {
                                        grid.getTile(x, y)->cross_check = false;
                                    }
                                }
                                std::set<Placement> placements = solutionBuilder.solve(input);
                                if(!placements.empty()) {
                                    const Placement &highest_scoring_placement = *placements.rbegin();
                                    grid.insert(highest_scoring_placement.x, highest_scoring_placement.y, highest_scoring_placement.horizontal, highest_scoring_placement.letters);
                                }
                                for(const Placement& placement : placements) {
                                    printf("(%d,%d) %c: %s (score: %d)\n", placement.x, placement.y, placement.horizontal ? 'H' : 'V', placement.word.data(), placement.score);
                                }
                            }
                            break;
                        case SDLK_BACKSPACE:
                            if(input.length() > 0)
                            {
                                input.pop_back();
                            }
                            break;
                        }
                    }

                    SDL_Rect messageRect = {.x = 0, .y = 0, .w = windowSurface->w, .h = TILE_SIZE};
                    SDL_FillRect(windowSurface, &messageRect, validationResult ? 0x000000 : 0xDD0000);

                    for(int i = 0; i < validationMessage.length(); i++)
                    {
                        renderCharacter(windowSurface, fontMap, i, 0, 10, 16, validationMessage[i]);
                    }

                    SDL_Surface *gridSurface = renderGrid(grid, cursor, fontMap);
                    SDL_Rect gridRect = {.x = 0, .y = GRID_OFFSET, .w = 0, .h = 0};
                    SDL_BlitSurface(gridSurface, NULL, windowSurface, &gridRect);
                    SDL_FreeSurface(gridSurface);

                    SDL_Surface * inputSurface = renderInput(input, cursor, fontMap);
                    SDL_Rect inputRect = {.x = 0, .y = TILE_SIZE * GRID_SIZE_Y + GRID_OFFSET, .w = 0, .h = 0};
                    SDL_BlitSurface(inputSurface, NULL, windowSurface, &inputRect);
                    SDL_FreeSurface(inputSurface);

                    SDL_UpdateWindowSurface(window);
                }
            }
            SDL_FreeSurface(fontMap);
        }
        else
        {
            std::cerr << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        }
        SDL_Quit();
    }
    else
    {
        std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
    }

    return 0;
}
