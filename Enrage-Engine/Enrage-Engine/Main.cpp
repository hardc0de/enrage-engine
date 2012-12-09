#include <string>

#include "Models/Display.h"
#include "Models/Map.h"
#include "Models/Player.h"
#include "Models/Renderer.h"
#include "Models/Image.h"
#include "Models/ObjectManager.h"

#include "Constants/Definitions.h"

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1 || TTF_Init() == -1)
        return -1;

    SDL_WM_SetCaption("ENRAGE Tech Demo", 0);

    bool exit = false;

    uint time = SDL_GetTicks();

    const uint mapWidth  = 19;
    const uint mapHeight = 19;

    int mapTiles[mapWidth][mapHeight] = 
    {
        {1 , 1 , 2 , 10, 2 , 1 , 1 , 9 , 9 , 9 , 9 , 9 , 9 , 10, 10, 11, 10, 10, 5 },
        {2 , 0 , 0 , 0 , 0 , 0 , 9 , 0 , 0 , 0 , 0 , 0 , 5 , 0 , 0 , 0 , 0 , 0 , 5 },
        {3 , 0 , 0 , 0 , 0 , 0 , 9 , 6 , 5 , 0 , 5 , 0 , 6 , 0 , 0 , 0 , 0 , 0 , 6 },
        {10, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 6 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 7 },
        {3 , 0 , 0 , 0 , 0 , 0 , 9 , 6 , 5 , 0 , 5 , 0 , 6 , 0 , 0 , 0 , 0 , 0 , 8 },
        {2 , 0 , 0 , 0 , 0 , 0 , 9 , 0 , 0 , 0 , 0 , 0 , 5 , 0 , 0 , 0 , 0 , 0 , 5 },
        {1 , 1 , 2 , 0 , 2 , 1 , 1 , 9 , 9 , 9 , 9 , 9 , 1 , 10, 10, 11, 10, 10, 1 },
        {1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        {1 , 0 , 4 , 4 , 4 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        {1 , 0 , 4 , 4 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
        {1 , 0 , 4 , 4 , 4 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        {1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 },
        {12, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 12, 0 , 0 , 0 , 0 , 0 , 1 },
        {12, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 12, 0 , 0 , 0 , 0 , 0 , 1 },
        {12, 0 , 0 , 9 , 0 , 0 , 9 , 0 , 0 , 9 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 },
        {12, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 12, 0 , 0 , 0 , 0 , 0 , 1 },
        {12, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 12, 0 , 0 , 0 , 0 , 0 , 1 },
        {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1 , 1 , 1 , 1 , 1 , 1 }
    };

    int** mapTiles2 = new int* [mapWidth];

    for(int i = 0; i < mapWidth; i++)
        mapTiles2[i] = new int[mapHeight];

    for(int i = 0; i < mapWidth; i++)
    {
        for(int j = 0; j < mapHeight; j++)
            mapTiles2[i][j] = mapTiles[i][j];
    }

    const uint textureCount = 15;

    std::string textures[textureCount] =
    {
        "resources/textures/tile_wall_1.bmp",
        "resources/textures/tile_wall_2.bmp",
        "resources/textures/tile_wall_3.bmp",
        "resources/textures/computer.bmp",
        "resources/textures/computer_tile_1.bmp",
        "resources/textures/computer_tile_2.bmp",
        "resources/textures/computer_tile_3.bmp",
        "resources/textures/computer_tile_4.bmp",
        "resources/textures/computer_bars.bmp",
        "resources/textures/pipes_bars.bmp",
        "resources/textures/lights_bars_anim.bmp",
        "resources/textures/fire.bmp",
        "resources/textures/door1.bmp",
        "resources/textures/light_ceiling.bmp",
        "resources/textures/tile_floor.bmp"
    };

    uint textureFrames[textureCount] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 1};
    uint textureTimes[textureCount] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 500, 100, 0, 0, 0};
    
    ObjectManager* objectManager = new ObjectManager(10);

    objectManager -> AddSprite(new Sprite(new Image("resources/textures/techlamp.bmp"), 2, 2));
    objectManager -> AddSprite(new Sprite(new Image("resources/textures/techlamp.bmp"), 5, 2));
    objectManager -> AddSprite(new Sprite(new Image("resources/textures/techlamp.bmp"), 2, 5));
    objectManager -> AddSprite(new Sprite(new Image("resources/textures/techlamp.bmp"), 5, 5));
    objectManager -> AddSprite(new Sprite(new Image("resources/textures/techlamp.bmp"), 3.5, 3.5));
    objectManager -> AddSprite(new Sprite(new Image("resources/textures/exit.bmp"), 12.5, 15.5));
    objectManager -> AddSprite(new Sprite(new AnimatedImage("resources/textures/firestick_anim.bmp", 4, 100), 15.5, 15.5));

    /*const uint mapWidth = 24;
    const uint mapHeight = 24;

    int mapTiles[mapWidth][mapHeight] =
    {
        {2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {2,0,0,0,0,0,5,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {2,2,2,0,2,2,5,2,0,2,4,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,4,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {2,0,0,0,0,0,5,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,4,4,0,4,4,4,4,0,4,4,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {4,0,0,0,0,0,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {4,0,0,0,0,0,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
        "resources/textures/fire.bmp",
        "resources/textures/lightceiling.bmp",
        "resources/textures/water.bmp"
    };

    uint textureFrames[textureCount] = {1, 1, 1, 1, 1, 3, 1, 4};
    uint textureTimes[textureCount] = {0, 0, 0, 0, 0, 100, 0, 100};
    
    ObjectManager* objectManager = new ObjectManager(10);

    objectManager -> AddSprite(new Sprite(new Image("resources/textures/baron.bmp"), 15, 15));
    objectManager -> AddSprite(new Sprite(new Image("resources/textures/baron.bmp"), 16, 15));*/

    Map* map = new Map((int**)mapTiles2, mapWidth, mapHeight, textures, textureFrames, textureTimes, textureCount, TEXTURE_SIZE, textureCount - 2, textureCount - 1, textureCount - 3, false, 8);
    Display* display = new Display(640, 480, 32, true, true, false, true);
    Player* player = new Player(map, 3.5, 15.5, -1.0, 0.0, 0.0, 0.66, 0.1);
    player -> Rotate(90 * 3.1415926535 / 180);

    Renderer* renderer = new Renderer(display, objectManager);

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
                    if (event.key.keysym.sym == SDLK_6)
                        renderer -> SetUsesNegative(!renderer -> UsesNegative());
                    if (event.key.keysym.sym == SDLK_7)
                        renderer -> SetUsesSepia(!renderer -> UsesSepia());
                    if (event.key.keysym.sym == SDLK_8)
                        map -> SetUsesFog(!map -> UsesFog());
                    if (event.key.keysym.sym == SDLK_9)
                        map -> SetFogDistance(map -> GetFogDistance() - 0.25);
                    if (event.key.keysym.sym == SDLK_0)
                        map -> SetFogDistance(map -> GetFogDistance() + 0.25);
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

            player -> MoveThink();
            display -> Clear();
            renderer -> Draw(map, player);

            map -> UpdateMap();
            objectManager -> Update();
        }
    }

    delete display;
    delete player;
    delete map;
    delete renderer;

    SDL_Quit();
    return 0;
}
