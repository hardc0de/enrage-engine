#include <cstdlib>
#include "SDL.h"
#include "../Constants/Definitions.h"
#include "Image.h"
#include "AnimatedImage.h"
#include "Sprite.h"
#include <string>

#pragma once

#ifndef MAP_H
#define MAP_H

class Map
{
private:
    int** map;
    IImage** textures;

    uint textureCount;
    uint textureSize;

    uint width;
    uint height;

    uint floorTextureIndex;
    uint ceilingTextureIndex;
    uint doorTextureIndex;

    bool useFog;
    double fogDistance;
    double inversefogDistance;

    struct mapFile
    {
        char header[10];
        uint width;
        uint height;
        int** map;
    };

public:
    Map();
    Map(int** map, uint width, uint height, std::string* texturePaths, uint* animatedTextureFrameCount, uint* animatedTextureDuration, uint textureCount, uint textureSize, uint ceilingTextureIndex, uint floorTextureIndex, uint doorTextureIndex, bool useFog, double fogDistance);
    Map(FILE* mapFile);
    ~Map();

    void UpdateMap();

    uint GetWidth();
    uint GetHeight();

    uint GetCeilingTextureIndex();
    uint GetFloorTextureIndex();
    uint GetDoorTextureIndex();

    bool UsesFog();
    void SetUsesFog(bool usesFog);

    double GetFogDistance();
    void SetFogDistance(double fogDistance);
    double GetInverseFogDistance();

    int GetTileAtPosition(uint x, uint y);
    uint GetTextureSize();

    IImage* GetTexture(uint index);

    class IndexOutOfBounds{};
};

#endif // MAP_H
