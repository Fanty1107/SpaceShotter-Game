#pragma once
#include "raylib.h"
//background variables
#define BACKGROUND_SIZE 800.0f
//screen variables
#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 800.0f
//player variables
#define PLAYER_X SCREEN_WIDTH/2.0f
#define PLAYER_Y SCREEN_HEIGHT/2.0f
//menu variables
#define FONT_SIZE 30

class Background {
public:
    Background();
    Texture2D background;
    Rectangle src;
    Rectangle dest;
    Vector2 origin;
    Color cor;
};

class Player {
public:
    Player();
    Texture2D sprite;
    Vector2 posV;
    float speed;
};