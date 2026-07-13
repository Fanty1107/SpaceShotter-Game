#pragma once
#include "gameObjects.hpp"
#include <vector>

class Game {
public:
    Game();
    void Initialize();
    void Update();
    void Draw();
    void Unload();

private:
    bool gameLoop;
    Background bg;
    Player ship;
    Texture2D plasmaSprite;
    std::vector<Shot> plasmas;
};