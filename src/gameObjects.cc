#include "gameObjects.h"

Background::Background() {
    background = LoadTexture("assets/BG.png");
    src = {0.0f, 0.0f, BACKGROUND_SIZE, BACKGROUND_SIZE};
    dest = {0.0f, 0.0f, BACKGROUND_SIZE, BACKGROUND_SIZE};
    origin = {0.0f, 0.0f};
    cor = WHITE;
}

Player::Player() {
    sprite = LoadTexture("assets/Player/player_b_m.png");
    posV = {PLAYER_X, PLAYER_Y};
    collider = {posV.x, posV.y, (float)sprite.width, (float)sprite.height};
    speed = 700.0f;
    fireRate = 0.3f;
    fireTimer = 0.0f;
}
Shot::Shot(Vector2 pos, float w, float h) {
    posV = pos;
    collider = {posV.x, posV.y, w, h};
    speed = 1000.0f;
};
 

