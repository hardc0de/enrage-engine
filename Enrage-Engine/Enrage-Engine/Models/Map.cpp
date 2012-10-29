#include "Map.h"

Map::Map(int** map, uint width, uint height, std::string* texturePaths, uint textureCount, uint textureSize)
{
    this -> width = width;
    this -> height = height;
    this -> map = new int* [width];
    
    for(uint i = 0; i < width; i++)
        this -> map[i] = new int [height];

    for(uint i = 0; i < width; i++)
    {
        for(uint j = 0; j < height; j++)
            this -> map[i][j] = map[i][j];
    }

    this -> textures = new Image*[textureCount];

    for(uint i = 0; i < textureCount; i++)
        this -> textures[i] = new Image(texturePaths[i].c_str());

    this -> textureCount = textureCount;
    this -> textureSize = textureSize;
}

Map::~Map()
{
    if(map)
    {
        for(uint i = 0; i < width; i++)
            delete[] map[i];

        delete[] map;
    }

    if(textures)
    {
        for(uint i = 0; i < textureCount; i++)
            delete textures[i];

        delete[] textures;
    }
}

uint Map::GetWidth()
{
    return width;
}

uint Map::GetHeight()
{
    return height;
}

int Map::GetTileAtPosition(uint x, uint y)
{
    if(x >= width || y >= height)
        throw IndexOutOfBounds();

    return map[x][y];
}

uint Map::GetTextureSize()
{
    return textureSize;
}

Image* Map::GetTexture(uint index)
{
    return textures[index];
}
