#pragma once
#include "raylib.h"

class Background {
public:
    Background();
    Texture2D background;
    Rectangle src;
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