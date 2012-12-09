#include "Image.h"
#include "AnimatedImage.h"

#pragma once

#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
private:
    IImage* sprite;
    
    double x;
    double y;

public:
    Sprite();
    Sprite(IImage* sprite, double x, double y);
    ~Sprite();

    IImage* GetSprite();

    double GetXPosition();
    double GetYPosition();

    void SetXPosition(double x);
    void SetYPosition(double y);

    class ImageFileNotFound{};
};

#endif // SPRITE_H