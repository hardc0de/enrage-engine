#include <SDL.h>
#include <SDL_image.h>
#include "../Constants/Definitions.h"
#include <string>

#pragma once

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
private:
    SDL_Surface* image;
    uint width;
    uint height;

public:
    Image();
    Image(std::string path);
    ~Image();

    uint* pixels;

    uint GetPixel(uint x, uint y);
    uint GetWidth();
    uint GetHeight();

    class ImageFileNotFound{};
};

#endif // IMAGE_H
