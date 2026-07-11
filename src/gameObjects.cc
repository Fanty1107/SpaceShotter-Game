#include "gameObjects.h"

Background::Background() {
    background = LoadTexture("assets/BG.png");
    src = {0.0f, 10.0f, 1000.0f, 800.0f};
    origin = {0.0f, 0.0f};
    cor = WHITE;
}

Player::Player() {
    sprite = LoadTexture("assets/Player/player_b_m.png");
    posV = {400.0f, 400.0f};
    speed = 400.0f;
}
