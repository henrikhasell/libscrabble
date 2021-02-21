#ifndef WORDS_WITH_FRIENDS_GUI_TEXT_HPP
#define WORDS_WITH_FRIENDS_GUI_TEXT_HPP

#include <SDL2/SDL.h>

void renderCharacter(
    SDL_Surface *dstSurface,
    SDL_Surface *srcSurface,
    int x, int y, int w, int h,
    unsigned char value);

#endif