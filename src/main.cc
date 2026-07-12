#include "raylib.h"
#include "gameObjects.h"
#include "raygui.h"



int main() {
    //window config
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Shooter");
    SetTargetFPS(60);

    //GameObjects
    Background bg;
    Player ship;  
    bool gameLoop = false;
    //GUI
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    while (!WindowShouldClose()) {
        //input/mov
        if(gameLoop){
        float deltaTime = GetFrameTime();
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) ship.posV.x += ship.speed * deltaTime;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  ship.posV.x -= ship.speed * deltaTime;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))    ship.posV.y -= ship.speed * deltaTime;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))  ship.posV.y += ship.speed * deltaTime;
        }
        //Draw functions
        BeginDrawing();
        ClearBackground(RAYWHITE); 

        if(!gameLoop){
            if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 15, 200, 30}, "Start Game")){
                gameLoop = true;
            }
        }
        else
        { 
            DrawTexturePro(bg.background,bg.src, bg.dest, bg.origin, 0.0f, bg.cor);
            DrawTextureV(ship.sprite, ship.posV, RAYWHITE);
        }
        EndDrawing();
    }

    //free all memory allocated by ram and gpu(vram)
    UnloadTexture(bg.background);
    UnloadTexture(ship.sprite);
    CloseWindow();
    
    return 0;
}