#include "Map.h"

Map::Map(int** map, uint width, uint height, std::string* texturePaths, uint* animatedTextureFrameCount, uint* animatedTextureDuration, uint textureCount, uint textureSize, uint ceilingTextureIndex, uint floorTextureIndex, uint doorTextureIndex, bool useFog, double fogDistance)
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

    this -> textures = new IImage*[textureCount];

    for(uint i = 0; i < textureCount; i++)
    {
        if(animatedTextureFrameCount[i] <= 1)
            this -> textures[i] = new Image(texturePaths[i].c_str());
        else
            this -> textures[i] = new AnimatedImage(texturePaths[i].c_str(), animatedTextureFrameCount[i], animatedTextureDuration[i]);
    }

    this -> textureCount = textureCount;
    this -> textureSize = textureSize;

    this -> ceilingTextureIndex = ceilingTextureIndex;
    this -> floorTextureIndex = floorTextureIndex;
    this -> doorTextureIndex = doorTextureIndex;

    this -> useFog = useFog;
    this -> fogDistance = fogDistance;

    inversefogDistance = 1 / this -> fogDistance;
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

void Map::UpdateMap()
{
    for(uint i = 0; i < textureCount; i++)
        textures[i] -> UpdateImage();
}

uint Map::GetWidth()
{
    return width;
}

uint Map::GetHeight()
{
    return height;
}

uint Map::GetCeilingTextureIndex()
{
    return ceilingTextureIndex;
}

uint Map::GetFloorTextureIndex()
{
    return floorTextureIndex;
}

uint Map::GetDoorTextureIndex()
{
    return doorTextureIndex;
}

bool Map::UsesFog()
{
    return useFog;
}

void Map::SetUsesFog(bool usesFog)
{
    this -> useFog = usesFog;
}

double Map::GetFogDistance()
{
    return fogDistance;
}

void Map::SetFogDistance(double fogDistance)
{
    if(fogDistance < 1)
        this -> fogDistance = 1;
    else
    {
        this -> fogDistance = fogDistance;
        this -> inversefogDistance = 1 / fogDistance;
    }
}

double Map::GetInverseFogDistance()
{
    return inversefogDistance;
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

IImage* Map::GetTexture(uint index)
{
    return textures[index];
}
