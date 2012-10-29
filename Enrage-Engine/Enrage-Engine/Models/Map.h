#include <cstdlib>
#include "SDL.h"
#include "../Constants/Definitions.h"
#include "Image.h"
#include <string>

#pragma once

#ifndef MAP_H
#define MAP_H

class Map
{
private:
    int** map;
    Image** textures;
    uint textureCount;
    uint textureSize;

    uint width;
    uint height;

    struct mapFile
    {
        char header[10];
        uint width;
        uint height;
        int** map;
    };

public:
    Map();
    Map(int** map, uint width, uint height, std::string* texturePaths, uint textureCount, uint textureSize);
    Map(FILE* mapFile);
    ~Map();

    uint GetWidth();
    uint GetHeight();

    int GetTileAtPosition(uint x, uint y);
    uint GetTextureSize();

    Image* GetTexture(uint index);

    class IndexOutOfBounds{};
};

#endif // MAP_H
