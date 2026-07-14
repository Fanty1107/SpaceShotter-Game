#pragma once
#include "gameObjects.hpp"
#include <raylib.h>
#include <vector>

class Game {
public:
    Game();
    void Initialize();
    void Update();
    void Draw();
    void Unload();

private:
    int pontos;
    bool gameLoop;
    Background bg;
    Player ship;
    //enemy
    std::vector<Enemy> enemies;
    std::vector<Shot> enemyPlasmas;
    Texture2D enemySprite;
    Texture2D enemySpriteWhite;
    float spawnTimer;
    //end enemy
    Texture2D plasmaSprite;
    Texture2D plasmaSpriteEnemy;
    std::vector<Shot> plasmas;
};