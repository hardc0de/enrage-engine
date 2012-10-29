#include "SDL.h"

class Game
{
public:
    Game();
    ~Game();

    void Run();
    void UnloadGame();

    virtual void Initialize();
    virtual void LoadContent();
    virtual void UnloadContent();
    virtual void Update();
    virtual void Draw();
};
