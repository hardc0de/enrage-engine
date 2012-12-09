#include "Sprite.h"
#include "../Constants/Definitions.h"

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#pragma once

class ObjectManager
{
public:
    ObjectManager();
    ObjectManager(uint size);
    ~ObjectManager();

    void Update();

    void AddSprite(Sprite* sprite);
    void RemoveSprites();

    Sprite* GetSpriteAtIndex(uint index);
    uint GetSpriteCount();

    void Sort();

    class IndexOutOfBounds{};

    uint* renderingSpriteOrder;
    double* renderingSpriteDistance;

private:
    Sprite** spriteVector;
    uint spriteCount;
};

#endif // OBJECTMANAGER_H