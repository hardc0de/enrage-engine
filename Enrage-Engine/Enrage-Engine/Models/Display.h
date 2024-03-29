#include "SDL.h"
#include "SDL_ttf.h"
#include "../Constants/Definitions.h"

#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

class Display
{
private:
    uint width;
    uint height;
    
    uint bpp;
    
    SDL_Surface* buffer;
    SDL_Surface* screen;
    SDL_Surface* textSurface;

    TTF_Font* font;

    bool drawText;

public:
    Display();
    Display(uint width, uint height, uint bpp, bool hardwareSurface, bool doubleBuffering, bool useHardwareAcceleration, bool fullScreen);
    ~Display();

    uint* pixels;

    uint GetWidth();
    uint GetHeight();

    uint GetPixel(uint x, uint y);
    void PutPixel(uint x, uint y, uint value);
    void DrawVerticalLine(uint x, uint yStart, uint yEnd, uint value);
    void DrawRectangle(uint xStart, uint yStart, uint xEnd, uint yEnd, uint value);
    void DrawText(char* text);
    void Clear();
    void Redraw();

    class DisplayCreationError{};
    class IndexOutOfBounds{};
};

#endif // DISPLAY_H