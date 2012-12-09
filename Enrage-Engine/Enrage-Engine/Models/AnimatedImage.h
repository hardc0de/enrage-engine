#include "IImage.h"

#pragma once

#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

class AnimatedImage : public IImage
{
private:
    SDL_Surface* image;
    uint* pixels;

    uint width;
    uint height;

    uint frameWidth;
    uint frameHeight;
    uint frameCount;

    uint frameDuration;
    uint currentFrame;

    uint refCount;
    uint lastFrameUpdate;

public:
    AnimatedImage();
    AnimatedImage(std::string path, uint framecount, uint frameDuration);
    ~AnimatedImage();

    uint GetPixel(uint x, uint y);
    uint GetWidth();
    uint GetHeight();

    uint GetRefCount();
    void IncrementRefCount();
    void UpdateImage();

    class InvalidImageSize{};
};

#endif // ANIMATEDIMAGE_H