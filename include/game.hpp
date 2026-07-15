#pragma once
#include "animation.hpp"
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
    bool quitGame;
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
    float spawnRate;
    //end enemy
    Texture2D plasmaSprite;
    Texture2D plasmaSpriteEnemy;
    std::vector<Shot> plasmas;
    Sound eva;
    Sound explosion;
    Sound coolSong;
    Sound gameOver;
    bool gameNormal;
    bool gameEVA;
    std::vector<Explosion> explosions;
    MultiImageAnimation explosionAnimGlobal;
};