#include "raylib.h"
#include "gameObjects.h"


int main() {
    //window config
    InitWindow(800, 800, "Space Shooter");
    SetTargetFPS(60);

    //GameObjects
    Background bg;
    Player ship;  

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