#include <SDL.h>
#include <SDL_image.h>
#include "../Constants/Definitions.h"
#include <string>

#pragma once

#ifndef IIMAGE_H
#define IIMAGE_H

class IImage
{
public:
    virtual uint GetPixel(uint x, uint y) = 0;
    virtual uint GetWidth() = 0;
    virtual uint GetHeight() = 0;

    virtual uint GetRefCount() = 0;
    virtual void IncrementRefCount() = 0;
    virtual void UpdateImage() = 0;
};

#endif // IIMAGE_H