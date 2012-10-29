#include "Image.h"

Image::Image()
{
    image = NULL;
    pixels = NULL;
    width = 0;
    height = 0;
}

Image::Image(std::string path)
{
    SDL_Surface* tempImage = IMG_Load(path.c_str());
    SDL_Surface* sourceImage;

    if(!tempImage)
        throw ImageFileNotFound();

    if(tempImage -> format -> BitsPerPixel < 32)
    {
        SDL_Surface* x = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        sourceImage = SDL_ConvertSurface(tempImage, x -> format, SDL_SWSURFACE);
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
}

Image::~Image()
{
    if(image)
        SDL_FreeSurface(image);

    width = 0;
    height = 0;
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
