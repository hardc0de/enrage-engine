#include "AnimatedImage.h"

AnimatedImage::AnimatedImage()
{
    width = TEXTURE_SIZE;
    height = TEXTURE_SIZE;
    frameWidth = TEXTURE_SIZE;
    frameHeight = TEXTURE_SIZE;

    frameCount = 1;
    frameDuration = 0xFFFFFFFF;

    currentFrame = 0;

    refCount = 0;

    lastFrameUpdate = SDL_GetTicks();

    image = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    pixels = (uint*)image -> pixels;

    for(uint i = 0; i < width; i++)
    {
        for(uint j = 0; j < height; j++)
            pixels[j * width + i] = (i ^ j) & 0x000000FF | (((i ^ j) << 8) & 0x0000FF00) | (((i ^ j) << 16) & 0x00FF0000) | 0xFF000000;
    }
}

AnimatedImage::AnimatedImage(std::string path, uint frameCount, uint frameDuration)
{
    SDL_Surface* tempImage = IMG_Load(path.c_str());
    SDL_Surface* sourceImage;

    currentFrame = 0;
    refCount = 0;

    lastFrameUpdate = SDL_GetTicks();

    if(!tempImage)
    {
        width = TEXTURE_SIZE;
        height = TEXTURE_SIZE;
        frameWidth = TEXTURE_SIZE;
        frameHeight = TEXTURE_SIZE;

        frameCount = 1;

        image = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        pixels = (uint*)image -> pixels;

        for(uint i = 0; i < width; i++)
        {
            for(uint j = 0; j < height; j++) // Generate a texture in case the destination one does not exist under given path
                pixels[j * width + i] = (i ^ j) & 0x000000FF | (((i ^ j) << 8) & 0x0000FF00) | (((i ^ j) << 16) & 0x00FF0000) | 0xFF000000;
        }

        return;
    }

    if(tempImage -> format -> BitsPerPixel < 32)
    {
        SDL_Surface* x = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        sourceImage = SDL_ConvertSurface(tempImage, x -> format, SDL_HWSURFACE);
        SDL_FreeSurface(tempImage);
        SDL_FreeSurface(x);
    }
    else
        sourceImage = tempImage;

    this -> frameCount = frameCount;
    this -> frameDuration = frameDuration;

    width = sourceImage -> w;
    height = sourceImage -> h;

    if(width % frameCount != 0)
        throw InvalidImageSize();

    frameWidth = width / frameCount;
    frameHeight = height;

    image = SDL_CreateRGBSurface
    (
        SDL_SWSURFACE,
        sourceImage -> h,
        sourceImage -> w,
        sourceImage -> format -> BitsPerPixel,
        sourceImage -> format -> Rmask,
        sourceImage -> format -> Gmask,
        sourceImage -> format -> Bmask,
        sourceImage -> format -> Amask
    );

    pixels = (uint*)image -> pixels;
    uint* tempPixels = (uint*)sourceImage -> pixels;

    for(uint i = 0; i < width; i++)
    {
        for(uint j = 0; j < height; j++)
            pixels[i * height + j] = tempPixels[j * width + i];
    }

    SDL_FreeSurface(sourceImage);

    refCount = 0;
}

AnimatedImage::~AnimatedImage()
{
    if(refCount > 0)
        refCount--;
    else
    {
        if(image)
            SDL_FreeSurface(image);

        width = 0;
        height = 0;
    }
}

uint AnimatedImage::GetPixel(uint x, uint y)
{
    uint* pixel = (uint*)image -> pixels + currentFrame * frameWidth * frameHeight + y + height * x;
    return *pixel;
}

uint AnimatedImage::GetWidth()
{
    return frameWidth;
}

uint AnimatedImage::GetHeight()
{
    return frameHeight;
}

uint AnimatedImage::GetRefCount()
{
    return refCount;
}

void AnimatedImage::IncrementRefCount()
{
    refCount++;
}

void AnimatedImage::UpdateImage()
{
    if(frameCount <= 1)
        return;

    if(SDL_GetTicks() >= lastFrameUpdate + frameDuration)
    {
        currentFrame++;

        if(currentFrame >= frameCount)
            currentFrame = 0;

        lastFrameUpdate = SDL_GetTicks();
    }
}
