#include <string>

#include "Models/Display.h"
#include "Models/Map.h"
#include "Models/Player.h"
#include "Models/Renderer.h"
#include "Models/Image.h"

#include "Constants/Definitions.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("RayCaster", 0);

    bool exit = false;

    uint time = SDL_GetTicks();

    const uint mapWidth = 24;
    const uint mapHeight = 24;

    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

    int mapTiles[mapWidth][mapHeight] =
    {
        {2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {2,0,0,0,0,0,5,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {2,2,2,0,2,2,5,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,4,4,0,4,4,4,4,0,4,4,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {6,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,4,0,4,4,4,4,4,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,4,4,4,4,4,4,4,4,6,4,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int** mapTiles2 = new int* [24];

    for(int i = 0; i < 24; i++)
        mapTiles2[i] = new int[24];

    for(int i = 0; i < 24; i++)
    {
        for(int j = 0; j < 24; j++)
            mapTiles2[i][j] = mapTiles[i][j];
    }

    const uint textureCount = 8;

    std::string textures[textureCount] =
    {
        "resources/textures/woodwall.bmp",
        "resources/textures/woodwall3.bmp",
        "resources/textures/woodencrate.bmp",
        "resources/textures/woodwall2.bmp",
        "resources/textures/bookcase.bmp",
        "resources/textures/door1.bmp",
        "resources/textures/lightceiling.bmp",
        "resources/textures/flatfloor.bmp"
    };

    Map* map = new Map((int**)mapTiles2, 24, 24, textures, textureCount, 512);
    Display* display = new Display(640, 480, 32, true, true);
    Player* player = new Player(map, 12.0, 12.0, -1.0, 0.0, 0.0, 0.66, 0.2);
    Renderer* renderer = new Renderer();

    //player -> SetSpeed(0.01);

    while(!exit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    exit = true;
                    break;

                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        exit = true;
                    if (event.key.keysym.sym == SDLK_UP)
                        player -> SetMoveForward(true);
                    if (event.key.keysym.sym == SDLK_DOWN)
                        player -> SetMoveBackwards(true);
                    if (event.key.keysym.sym == SDLK_LEFT)
                        player -> SetRotateLeft(true);
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        player -> SetRotateRight(true);
                    break;
                }

                case SDL_KEYUP:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        exit = true;
                    if (event.key.keysym.sym == SDLK_UP)
                        player -> SetMoveForward(false);
                    if (event.key.keysym.sym == SDLK_DOWN)
                        player -> SetMoveBackwards(false);
                    if (event.key.keysym.sym == SDLK_LEFT)
                        player -> SetRotateLeft(false);
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        player -> SetRotateRight(false);
                    break;
                }
            }
        }

        if(time < SDL_GetTicks())
        {
            display -> Redraw();
            time += 10;

            player -> Move();
            display -> Clear();
            renderer -> Draw(display, map, player);
        }
    }

    delete display;
    delete player;
    delete map;
    delete renderer;

    SDL_Quit();
    return 0;
}
