#include "Display.h"

Display::Display()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw DisplayCreationError();

    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    buffer = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, 640, 480, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    this -> width = 640;
    this -> height = 480;
    this -> bpp = 32;

    pixels = (uint*)buffer -> pixels;
}

Display::Display(uint width, uint height, uint bpp, bool hardwareSurface, bool doubleBuffering)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw DisplayCreationError();

    this -> width = width;
    this -> height = height;
    this -> bpp = bpp;

    screen = SDL_SetVideoMode(width, height, bpp, hardwareSurface ? SDL_HWSURFACE : 0 | doubleBuffering ? SDL_DOUBLEBUF : 0);
    buffer = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, width, height, bpp, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    pixels = (uint*)buffer -> pixels;
}

Display::~Display()
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(buffer);
    pixels = NULL;
}

uint Display::GetWidth()
{
    return width;
}

uint Display::GetHeight()
{
    return height;
}

void Display::PutPixel(uint x, uint y, uint value)
{
    if(x >= width || y >= height)
        throw IndexOutOfBounds();

    if(SDL_MUSTLOCK(screen))
        SDL_LockSurface(screen);

    pixels[x * height + y] = value;

    if(SDL_MUSTLOCK(screen))
        SDL_UnlockSurface(screen);
}

void Display::DrawVerticalLine(uint x, uint yStart, uint yEnd, uint value)
{
    uint* lineBuffer = pixels;

    lineBuffer += x * height + yStart;

    for(uint i = yStart; i < yEnd; i++)
    {
        *lineBuffer = value;
        lineBuffer++;
    }
}

void Display::DrawRectangle(uint xStart, uint yStart, uint xEnd, uint yEnd, uint value)
{
    //SDL_FillRect(screen, 
}

void Display::Clear()
{
    SDL_FillRect(buffer, 0, SDL_MapRGB(screen -> format, 0, 0, 0));
}

void Display::Redraw()
{
    uint* bufp;
    bufp = (uint*)screen -> pixels;
  
    for(uint y = 0; y < height; y++)
    {
        for(uint x = 0; x < width; x++)
        {
            *bufp = pixels[height * x + y];
            bufp++;
        }

        bufp += screen -> pitch / 4;
        bufp -= width;
    }

    SDL_Flip(screen);
}
