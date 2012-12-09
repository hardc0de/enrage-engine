#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
    spriteVector = NULL;
    spriteCount = 0;
    renderingSpriteOrder = NULL;
    renderingSpriteDistance = NULL;
}

ObjectManager::ObjectManager(uint size)
{
    spriteVector = new Sprite*[size];
    spriteCount = 0;

    renderingSpriteOrder = new uint[size];
    renderingSpriteDistance = new double[size];
}

ObjectManager::~ObjectManager()
{
    if(spriteVector)
    {
        for(uint i = 0; i < spriteCount; i++)
        {
            if(spriteVector[i] != NULL)
                delete spriteVector[i];
        }

        delete[] spriteVector;
    }

    if(renderingSpriteOrder)
        delete[] renderingSpriteOrder;

    if(renderingSpriteDistance)
        delete[] renderingSpriteDistance;

    spriteCount = 0;
}

void ObjectManager::Update()
{
    for(uint i = 0; i < spriteCount; i++)
        spriteVector[i] -> GetSprite() -> UpdateImage();
}

void ObjectManager::AddSprite(Sprite* sprite)
{
    spriteVector[spriteCount] = sprite;
    spriteCount++;
}

void ObjectManager::RemoveSprites()
{
    if(spriteVector && spriteCount > 0)
        for(uint i = 0; i < spriteCount; i++)
        {
            if(spriteVector[i] != NULL)
                delete spriteVector[i];
        }

    spriteCount = 0;
}

Sprite* ObjectManager::GetSpriteAtIndex(uint index)
{
    if(index < 0 || index >= spriteCount)
        throw IndexOutOfBounds();

    return spriteVector[index];
}

uint ObjectManager::GetSpriteCount()
{
    return spriteCount;
}

void ObjectManager::Sort()
{
    int gap = spriteCount;
    bool swapped = false;

    while(gap > 1 || swapped)
    {
        gap = (gap * 10) / 13;

        if(gap == 9 || gap == 10) 
            gap = 11;

        if (gap < 1) gap = 1;
            swapped = false;

        for (int i = 0; i < spriteCount - gap; i++)
        {
            int j = i + gap;

            if (renderingSpriteDistance[i] < renderingSpriteDistance[j])
            {
                std::swap(renderingSpriteDistance[i], renderingSpriteDistance[j]);
                std::swap(renderingSpriteOrder[i], renderingSpriteOrder[j]);
                swapped = true;
            }
        }
    }
}