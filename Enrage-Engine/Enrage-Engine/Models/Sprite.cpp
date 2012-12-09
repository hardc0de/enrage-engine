#include "Sprite.h"

Sprite::Sprite()
{
    sprite = new Image();
    
    x = 0.0;
    y = 0.0;
}

Sprite::Sprite(IImage* sprite, double x, double y)
{
    this -> sprite = sprite;

    if(sprite -> GetRefCount())
        sprite -> IncrementRefCount();

    this -> x = x;
    this -> y = y;
}

Sprite::~Sprite()
{
    if(sprite)
        delete sprite;

    x = 0.0;
    y = 0.0;
}

IImage* Sprite::GetSprite()
{
    return sprite;
}

double Sprite::GetXPosition()
{
    return x;
}

double Sprite::GetYPosition()
{
    return y;
}

void Sprite::SetXPosition(double x)
{
    this -> x = x;
}

void Sprite::SetYPosition(double y)
{
    this -> y = y;
}

