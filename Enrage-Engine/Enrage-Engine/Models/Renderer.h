#include "SDL.h"
#include "../Constants/Definitions.h"
#include "Display.h"
#include "Player.h"
#include "Map.h"
#include "ObjectManager.h"
#include <cmath>
#include <cstdlib>

#pragma once

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
    Renderer::Renderer();
    Renderer(Display* display, ObjectManager* objectManager);
    ~Renderer();

    void Draw(Map* map, Player* player);
    uint Sepia(uint color);
    uint Fog(uint color, double distance, double fogDistance, double inverseFogDistance);
    uint Negative(uint color);

    bool UsesSepia();
    void SetUsesSepia(bool useSepia);

    bool UsesNegative();
    void SetUsesNegative(bool useNegative);

private:
    Display* display;
    ObjectManager* objectManager;
    double* floorCastingLookupTable;
    uint lookupTableSize;
    uint* zBuffer;
    bool useSepia;
    bool useNegative;

    char debugTextBuffer[512];
};

#endif // RENDERER_H