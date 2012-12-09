#include "IImage.h"
#include "../Constants/Definitions.h"

#pragma once

#ifndef IMAGE_H
#define IMAGE_H

class Image : public IImage
{
private:
    SDL_Surface* image;
    uint* pixels;
    uint width;
    uint height;
    uint refCount;

public:
    Image();
    Image(std::string path);
    ~Image();

    uint GetPixel(uint x, uint y);
    uint GetWidth();
    uint GetHeight();

    uint GetRefCount();
    void IncrementRefCount();
    void UpdateImage();
};

#endif // IMAGE_H
