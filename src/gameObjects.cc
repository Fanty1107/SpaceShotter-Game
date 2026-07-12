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
    speed = 400.0f;
}
