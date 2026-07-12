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
        //collision detection implementation later

        //Draw functions
        BeginDrawing();
        ClearBackground(RAYWHITE); 

        if(!gameLoop){
            //menu logic here
            float buttonWidth = 200;
            float buttonHeight = 30;
            float buttonX = (SCREEN_WIDTH/ 2 ) - (buttonWidth / 2);
            float buttonY = (SCREEN_HEIGHT/2) - (buttonHeight / 2);

            ClearBackground(BLACK);

            DrawText("Space Shooter", SCREEN_WIDTH/2 - MeasureText("Space Shooter", FONT_SIZE)/2, (int)SCREEN_HEIGHT/4,
             FONT_SIZE, PURPLE);

            DrawText("Press the button to start the game", SCREEN_WIDTH/2 - MeasureText("Press the button to start the game",
                 FONT_SIZE)/2, (int)SCREEN_HEIGHT/3, FONT_SIZE, GRAY);

            if(GuiButton((Rectangle){buttonX, buttonY, buttonWidth, buttonHeight}, "Start Game")){
                gameLoop = true;
            }
        }
        else
        { 
            //game logic here
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