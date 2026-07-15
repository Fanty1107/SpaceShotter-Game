#include "gameObjects.hpp"
#include "animation.hpp"
#include <raylib.h>
#include <vector>

// --- BACKGROUND ---
void Background::Load() {
    background = LoadTexture("assets/BG.png");
    src = {0.0f, 0.0f, BACKGROUND_SIZE, BACKGROUND_SIZE};
    dest = {0.0f, 0.0f, BACKGROUND_SIZE, BACKGROUND_SIZE};
    origin = {0.0f, 0.0f};
    cor = WHITE;
}
void Background::Draw() { DrawTexturePro(background, src, dest, origin, 0.0f, cor); }
void Background::Unload() { UnloadTexture(background); }

// --- SHOT ---
Shot::Shot(Vector2 pos, float w, float h, float directionY) {
    posV = pos;
    collider = {posV.x, posV.y, w, h};
    speed = 1000.0f;
    dirY = directionY;
}
void Shot::Update(float deltaTime) {
    posV.y += (speed * dirY) * deltaTime;
    collider.x = posV.x;
    collider.y = posV.y;
}
void Shot::Draw(Texture2D& sprite) {
    DrawTextureV(sprite, posV, RAYWHITE);
}

// --- PLAYER ---
Player::Player() {
    posV = {PLAYER_X, PLAYER_Y};
    direction = UPDOWN;
    speed = 400.0f;
    fireRate = 0.2f;
    fireTimer = 0.0f;

    hp = 5;
    blinkTimer = 0.0f;
    isDead = false;
}

void Player::Load() {
    sprite = LoadTexture("assets/Player/player_b_m.png");
    spriteWhite = LoadTexture("assets/Player/player_b_m_white.png");
    collider = {posV.x, posV.y, (float)sprite.width, (float)sprite.height};

    // Load Animations
    std::vector<Texture2D> framesL = {
        LoadTexture("assets/Player/player_b_l2.png"),
        LoadTexture("assets/Player/player_b_l1.png")
    };
    animL = MultiImageAnimation(framesL, 0.1f);

    std::vector<Texture2D> framesR = {
        LoadTexture("assets/Player/player_b_r1.png"),
        LoadTexture("assets/Player/player_b_r2.png")
    };
    animR = MultiImageAnimation(framesR, 0.1f);
}

void Player::Update(float deltaTime, std::vector<Shot>& plasmas, Texture2D& plasmaSprite) {
    if(isDead) return;
    if(blinkTimer > 0.0f) blinkTimer -= deltaTime;

    animL.animationUpdate(deltaTime);
    animR.animationUpdate(deltaTime);
    fireTimer += deltaTime;

    // Movement
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) { 
        posV.x -= speed * deltaTime;
        direction = LEFT;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        posV.x += speed * deltaTime;
        direction = RIGHT;
    } else {
        direction = UPDOWN;
    }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))   posV.y -= speed * deltaTime;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) posV.y += speed * deltaTime;

    // Colisão Matemática com as bordas da tela (Muito mais leve que retângulos)
    if (posV.x < 0) posV.x = 0;
    if (posV.x > SCREEN_WIDTH - sprite.width) posV.x = SCREEN_WIDTH - sprite.width;
    if (posV.y < 0) posV.y = 0;
    if (posV.y > SCREEN_HEIGHT - sprite.height) posV.y = SCREEN_HEIGHT - sprite.height;

    collider.x = posV.x;
    collider.y = posV.y;

    // Tiro
    if ((IsKeyDown(KEY_SPACE) && fireTimer >= fireRate)) {
        Vector2 startPos = { posV.x + (float)sprite.width/2 - (float)plasmaSprite.width/2, posV.y };
        plasmas.push_back(Shot(startPos, (float)plasmaSprite.width, (float)plasmaSprite.height, -1.0f));
        fireTimer = 0.0f;
    }
}

void Player::Draw() {
    if(isDead) return;

    bool isFlashing = (blinkTimer > 0.0f) && ((int)(blinkTimer * 10) % 2 == 0);
    if (isFlashing) {
        DrawTextureV(spriteWhite, posV, RAYWHITE);
    }
    else{
    
    if (direction == LEFT) {
        DrawTextureV(animL.getCurrentFrame(), posV, RAYWHITE);
    } else if (direction == RIGHT) {
        DrawTextureV(animR.getCurrentFrame(), posV, RAYWHITE);
    } else {
        DrawTextureV(sprite, posV, RAYWHITE);
        }

    }
}

void Player::Unload() {
    UnloadTexture(sprite);
    UnloadTexture(spriteWhite);
    for (auto& tex : animL.frames) UnloadTexture(tex);
    for (auto& tex : animR.frames) UnloadTexture(tex);
}

// --- ENEMY ---
Enemy::Enemy(float startX) {
    posV = {startX, -50.0f}; //random position will be set later
    collider = {posV.x, posV.y, 0,0};
    speed = 200.0f;
    fireRate = 0.6f;
    fireTimer = 0.0f;
    hp = 2;
    blinkTimer = 0.0f;
}

void Enemy::Update(float deltaTime, std::vector<Shot>& plasmas, Texture2D& plasmaSprite, 
                   Texture2D& refSprite) {
    if(blinkTimer > 0.0f) blinkTimer -= deltaTime;

    fireTimer += deltaTime; 
    //mov down
    posV.y += speed * deltaTime;
    

    // Colisão Matemática com as bordas da tela (Muito mais leve que retângulos)
    if (posV.x < 0) posV.x = 0;
    if (posV.x > SCREEN_WIDTH - refSprite.width) posV.x = SCREEN_WIDTH - refSprite.width;

    collider.x = posV.x;
    collider.y = posV.y;
    collider.width = refSprite.width;
    collider.height = refSprite.height;

    // Tiro
    if (fireTimer >= fireRate) { //enemy always shoots
        Vector2 startPos = { 
            posV.x + (float)refSprite.width/2 - (float)plasmaSprite.width/2, 
            posV.y + (float)refSprite.height
        };
        Shot enemyShot(startPos, (float)plasmaSprite.width, (float)plasmaSprite.height, 1.0f);
        enemyShot.speed = 400.0f; 
        plasmas.push_back(enemyShot);
        fireTimer = 0.0f;
    }
}
void Enemy::Draw(Texture2D& refSprite, Texture2D& refSpriteWhite) {
    bool isFlashing = (blinkTimer > 0.0f) && ((int)(blinkTimer * 10) % 2 == 0);
    DrawTextureV(refSprite, posV, RAYWHITE);
    if (isFlashing) {
        // Desenha a silhueta branca
        DrawTextureV(refSpriteWhite, posV, RAYWHITE);
    }
}

Explosion::Explosion(Vector2 pos, MultiImageAnimation animation){
    posV = pos;
    anim = animation;

    lifeTime = anim.frames.size() * anim.frameTime;
}
void Explosion::Update(float deltaTime) {
    anim.animationUpdate(deltaTime);
    lifeTime -= deltaTime;
}

void Explosion::Draw() {
    DrawTextureV(anim.getCurrentFrame(), posV, RAYWHITE);
}

