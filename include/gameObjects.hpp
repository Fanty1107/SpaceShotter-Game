#pragma once
#include "raylib.h"
#include "animation.hpp"
#include <vector>

#define BACKGROUND_SIZE 800.0f
#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 800.0f
#define PLAYER_X SCREEN_WIDTH/2.0f
#define PLAYER_Y SCREEN_HEIGHT/2.0f
#define FPS 60
#define FONT_SIZE 30

enum Direction { LEFT, RIGHT, UPDOWN };

class Background {
public:
    void Load();
    void Draw();
    void Unload();
    
    Texture2D background;
    Rectangle src, dest;
    Vector2 origin;
    Color cor;
};

struct Shot {
    Shot(Vector2 pos, float w, float h, float directionY);
    void Update(float deltaTime);
    void Draw(Texture2D& sprite);
    
    Vector2 posV;
    Rectangle collider;
    float speed;
    float dirY;
};
struct Explosion{
    Explosion(Vector2 pos, MultiImageAnimation animation);
    void Update(float deltaTime);
    void Draw();

    Vector2 posV;
    MultiImageAnimation anim;
    float lifeTime;
};

class Player {
public:
    Player();
    void Load();
    void Update(float deltaTime, std::vector<Shot>& plasmas, Texture2D& plasmaSprite);
    void Draw();
    void Unload();

    Texture2D sprite;
    Texture2D spriteWhite;
    Vector2 posV;
    Rectangle collider;
    int direction;
    float speed;
    float fireRate;
    float fireTimer;

    int hp;
    float blinkTimer;
    bool isDead;

    MultiImageAnimation animL;
    MultiImageAnimation animR;
};

class Enemy {
public:
    Enemy(float startX);
  
    void Update(float deltaTime, std::vector<Shot>& plasmas, Texture2D& plasmaSprite, 
               Texture2D& refSprite);
    void Draw(Texture2D& refSprite , Texture2D& refSpriteWhite);

    Vector2 posV;
    Rectangle collider;
    int direction;
    float speed;
    float fireRate;
    float fireTimer;

    int hp;
    float blinkTimer;
};