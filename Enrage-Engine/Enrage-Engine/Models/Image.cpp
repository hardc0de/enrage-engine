#include "Image.h"

Image::Image()
{
    width = TEXTURE_SIZE;
    height = TEXTURE_SIZE;

    image = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    pixels = (uint*)image -> pixels;

    for(uint i = 0; i < width; i++)
    {
        for(uint j = 0; j < height; j++)
            pixels[j * width + i] = (i ^ j) & 0x000000FF | (((i ^ j) << 8) & 0x0000FF00) | (((i ^ j) << 16) & 0x00FF0000) | 0xFF000000;
    }

    refCount = 0;
}

Image::Image(std::string path)
{
    SDL_Surface* tempImage = IMG_Load(path.c_str());
    SDL_Surface* sourceImage;

    if(!tempImage)
    {
        width = TEXTURE_SIZE;
        height = TEXTURE_SIZE;

        image = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        pixels = (uint*)image -> pixels;

        for(uint i = 0; i < width; i++)
        {
            for(uint j = 0; j < height; j++) // Generate a texture in case the destination one does not exist under given path
                pixels[j * width + i] = (i ^ j) & 0x000000FF | (((i ^ j) << 8) & 0x0000FF00) | (((i ^ j) << 16) & 0x00FF0000) | 0xFF000000;
        }

        refCount = 0;

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

    width = sourceImage -> w;
    height = sourceImage -> h;

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

Image::~Image()
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

uint Image::GetPixel(uint x, uint y)
{
    uint* pixel = (uint*)image -> pixels + y + height * x;
    return *pixel;
}

uint Image::GetWidth()
{
    return width;
}

uint Image::GetHeight()
{
    return height;
}

uint Image::GetRefCount()
{
    return refCount;
}

void Image::IncrementRefCount()
{
    refCount++;
}

void Image::UpdateImage()
{
    // For the sake of AnimatedImage compatibility
}
