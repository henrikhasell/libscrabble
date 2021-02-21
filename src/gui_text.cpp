#include "gui_text.hpp"

#define GLYPH_W 8
#define GLYPH_H 8

void renderCharacter(
        SDL_Surface *dstSurface,
        SDL_Surface *srcSurface,
        int x, int y, int w, int h,
        unsigned char value)
{
    SDL_Rect srcRect, dstRect;

    srcRect.x = GLYPH_W * (value % 16);
    srcRect.y = GLYPH_H * (value / 16);
    srcRect.w = GLYPH_W;
    srcRect.h = GLYPH_H;

    dstRect.x = w * x;
    dstRect.y = h * y;
    dstRect.w = w;
    dstRect.h = h;

    SDL_BlitScaled(srcSurface, &srcRect, dstSurface, &dstRect);
}