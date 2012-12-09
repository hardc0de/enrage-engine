#include "Display.h"

Display::Display()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw DisplayCreationError();

    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    buffer = SDL_CreateRGBSurface(SDL_HWSURFACE, 640, 480, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    font = TTF_OpenFont("resources/fonts/DroidSans.ttf", 9);

    this -> width = 640;
    this -> height = 480;
    this -> bpp = 32;

    pixels = (uint*)buffer -> pixels;
    drawText = false;
}

Display::Display(uint width, uint height, uint bpp, bool hardwareSurface, bool doubleBuffering, bool useHardwareAcceleration, bool fullScreen)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw DisplayCreationError();

    this -> width = width;
    this -> height = height;
    this -> bpp = bpp;

    font = TTF_OpenFont("resources/fonts/DroidSans.ttf", 9);

    uint flags = 0;

    if(doubleBuffering)
        flags |= SDL_DOUBLEBUF;
    if(hardwareSurface)
        flags |= SDL_HWSURFACE;
    if(fullScreen)
        flags |= SDL_FULLSCREEN;

    screen = SDL_SetVideoMode(width, height, bpp, flags);
    buffer = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, bpp, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    pixels = (uint*)buffer -> pixels;
    drawText = false;
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

void Display::DrawText(char* text)
{
    SDL_Color textColor = {255, 255, 255, 255};
    textSurface = TTF_RenderText_Blended(font, text, textColor);

    drawText = true;
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

    if(drawText)
    {
        SDL_BlitSurface(textSurface, NULL, screen, NULL);
        drawText = false;
    }

    SDL_Flip(screen);
}
