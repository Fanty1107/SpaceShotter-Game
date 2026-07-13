#include "gameObjects.h"
#include "raygui.h"
#include <raylib.h>
#include <vector>



int main() {
    //window config
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Shooter");
    SetTargetFPS(60);

    //GameObjects
    Background bg;
    Player ship;
    Texture2D plasmaSprite = LoadTexture("assets/FX/plasma_1.png");
    std::vector<Shot> plasmas;
    bool gameLoop = false;
    //GUI
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    //colliders wall
    Rectangle topWall = {0, 0, SCREEN_WIDTH, 1};
    Rectangle bottomWall = {0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, 1};
    Rectangle leftWall = {0, 0, 1, SCREEN_HEIGHT};
    Rectangle rightWall = {SCREEN_WIDTH - 1, 0, 1, SCREEN_HEIGHT};

    while (!WindowShouldClose()) {

        //input/mov
        if(gameLoop){
        float deltaTime = GetFrameTime();
        ship.fireTimer += deltaTime;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) ship.posV.x += ship.speed * deltaTime;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  ship.posV.x -= ship.speed * deltaTime;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))    ship.posV.y -= ship.speed * deltaTime;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))  ship.posV.y += ship.speed * deltaTime;
        //shot logic    
        if((IsKeyDown(KEY_SPACE) && ship.fireTimer >= ship.fireRate)){
                Vector2 startPos = { 
                    ship.posV.x + (float)ship.sprite.width/2 - (float)plasmaSprite.width/2, 
                    ship.posV.y 
                };
            plasmas.push_back(Shot(startPos, (float)plasmaSprite.width, (float)plasmaSprite.height));
            ship.fireTimer = 0.0f; // Reset the fire timer
        }
        for (int i = plasmas.size() - 1; i >= 0; i--) {
                plasmas[i].posV.y -= plasmas[i].speed * deltaTime;
                plasmas[i].collider.x = plasmas[i].posV.x;
                plasmas[i].collider.y = plasmas[i].posV.y;
        
        if (plasmas[i].posV.y < -plasmaSprite.height) {
             plasmas.erase(plasmas.begin() + i);
            }
        }
        //collider update
        ship.collider.x = ship.posV.x;
        ship.collider.y = ship.posV.y;
        }
        //collision detection
        
         if(CheckCollisionRecs(topWall, ship.collider)){
            ship.posV.y *= 0.0f;
         }
         if(CheckCollisionRecs(bottomWall, ship.collider)){         
            ship.posV.y =  SCREEN_HEIGHT - ship.sprite.height;
         }
         if(CheckCollisionRecs(leftWall, ship.collider)){
            ship.posV.x *= 0.0f;
         }
        if(CheckCollisionRecs(rightWall, ship.collider)){         
            ship.posV.x =  SCREEN_WIDTH - ship.sprite.width;
            }
      
        //Draw functions
        BeginDrawing();
        ClearBackground(RAYWHITE); 

        if(!gameLoop){
            //menu logic here
            float buttonWidth = 200;
            float buttonHeight = 30;
            float buttonX = (SCREEN_WIDTH/ 2 ) - (buttonWidth / 2);
            float buttonY = (SCREEN_HEIGHT/2) - (buttonHeight / 2);
            Rectangle buttonRec = {buttonX, buttonY, buttonWidth, buttonHeight};

            ClearBackground(BLACK);

            DrawText("Space Shooter", SCREEN_WIDTH/2 - MeasureText("Space Shooter", FONT_SIZE)/2, (int)SCREEN_HEIGHT/4,
             FONT_SIZE, PURPLE);

            DrawText("Press the button to start the game", SCREEN_WIDTH/2 - MeasureText("Press the button to start the game",
                 FONT_SIZE)/2, (int)SCREEN_HEIGHT/3, FONT_SIZE, GRAY);

            if(GuiButton(buttonRec, "Start Game")){
                gameLoop = true;
            }
        }
        else
        { 
            //game here
            DrawTexturePro(bg.background,bg.src, bg.dest, bg.origin, 0.0f, bg.cor);
            for (size_t i = 0; i < plasmas.size(); i++) {
                DrawTextureV(plasmaSprite, plasmas[i].posV, RAYWHITE);

                //draw colliders for testing
                DrawRectangleLinesEx(plasmas[i].collider, 1, RED);
            }
            DrawTextureV(ship.sprite, ship.posV, RAYWHITE);
          
        }
        EndDrawing();
    }

    //free all memory allocated by ram and gpu(vram)
    UnloadTexture(bg.background);
    UnloadTexture(ship.sprite);
    UnloadTexture(plasmaSprite);
    CloseWindow();
    
    return 0;
}
