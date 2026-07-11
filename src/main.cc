#include "raylib.h"

struct Background {
    Texture2D background;
    Rectangle src;
    Vector2 origin;
    Color cor;
};

struct Player {
    Texture2D sprite;
    Vector2 posV;
    float speed;
};

int main() {
    //window config
    InitWindow(800, 800, "Space Shooter");
    SetTargetFPS(60);

    //GameObjects
    Background bg;
    bg.background = LoadTexture("assets/BG.png");
    bg.src = {0.0f, 10.0f, 1000.0f, 800.0f};
    bg.origin = {0.0f, 0.0f};
    bg.cor = WHITE;

    Player ship;  
    ship.sprite = LoadTexture("assets/Player/player_b_m.png");
    ship.posV = {400.0f, 400.0f};
    ship.speed = 400.0f;
   
    while (!WindowShouldClose()) {
        //input/mov
       

        //Draw functions
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(bg.background, bg.src, bg.origin, bg.cor);
        DrawTextureV(ship.sprite, ship.posV, RAYWHITE);
        
        EndDrawing();
    }

    //free all memory allocated by ram and gpu(vram)
    UnloadTexture(bg.background);
    UnloadTexture(ship.sprite);
    CloseWindow();
    
    return 0;
}