#include "SDL.h"
#include "../Constants/Definitions.h"
#include "Display.h"
#include "Player.h"
#include "Map.h"
#include <cmath>

#pragma once

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Draw(Display* display, Map* map, Player* player);
};

#endif // RENDERER_H